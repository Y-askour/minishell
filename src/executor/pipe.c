/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/25 20:43:20 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_out_check(t_pipe *in_out, int *i)
{
	in_out->in = 0;
	*i = 0;
	in_out->check = 0;
}

void	init_var(t_pipe *in_out, t_exec *var, t_env	*g_env, char **paths)
{
	pipe(in_out->fd);
	var->g_env = g_env;
	var->paths = paths;
	var->in = in_out->in;
	var->out = in_out->fd[1];
}

void	change_exitstatus(int n)
{
	if (n == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	else if (n == 3)
	{
		g_exit_status = 131;
		write(1, "Quit: 3\n", 8);
	}
}
int	pipes(int n, t_cmd_elem *head, char **paths, t_env *g_env)
{
	int			i;
	t_norm		norm;
	
	signal(SIGINT, SIG_IGN);
	init_out_check(&norm.in_out, &i);
	norm.ptr = head;
	while (i < n)
	{
		init_var(&norm.in_out, &norm.var, g_env, paths);
		if (i == 0)
			close(norm.in_out.fd[0]);
		norm.pid = executer(norm.ptr->args, n, i, norm.ptr, &norm.var);
		if (pipes_helper1(norm.pid, norm.in_out.in, norm.in_out.fd, \
		&norm.in_out.check))
			break ;
		pipes_helper2(&norm.ptr, norm.in_out.fd, &norm.in_out.in);
		i++;
	}
	if (builtins(head->args) && n == 1)
		pipes_helper3(norm.in_out.in, n);
	else
	{
		waitpid(norm.pid, &norm.status, 0);
		change_exitstatus(norm.status);
		pipes_helper3(norm.in_out.in, n);
	}
	end_pipes(paths);
	return (0);
}

int	pipeline(int n,	t_cmd_elem *head,	t_env *g_env)
{
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths(g_env);
	return (pipes(n, head, paths, g_env));
}

int	run_command(t_cmd_list *cmdline, t_env *g_env)
{
	int			i;
	t_cmd_elem	*ptr;

	i = 0;
	ptr = cmdline->head;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	ptr = cmdline->head;
	pipeline(i, ptr, g_env);
	return (0);
}

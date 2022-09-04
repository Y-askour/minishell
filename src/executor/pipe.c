/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/04 22:17:22 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting_processes(t_cmd_elem *head, int n, t_norm *norm)
{
	if (builtins(head->args) && n == 1)
		pipes_helper3(norm->in_out.in, n);
	else
	{
		waitpid(norm->pid, &norm->status, 0);
		change_exitstatus(norm->status);
		pipes_helper3(norm->in_out.in, n);
	}
}

int	pipes(int n, t_cmd_elem *head, char **paths, t_g_env *g_env)
{
	int			i;
	t_norm		norm;	

	signal(SIGINT, SIG_IGN);
	init_out_check(&norm.in_out, &i);
	norm.ptr = head;
	while (i < n)
	{
		init_var(&norm.in_out, &norm.var, g_env, paths);
		norm.pid = executer(n, i, norm.ptr, &norm.var);
		if (pipes_helper1(norm.pid, norm.in_out.in, norm.in_out.fd, \
		&norm.in_out.check))
			break ;
		pipes_helper2(&norm.ptr, norm.in_out.fd, &norm.in_out.in);
		i++;
	}
	waiting_processes(head, n, &norm);
	end_pipes(paths);
	return (0);
}

int	pipeline(int n,	t_cmd_elem *head,	t_g_env *g_env)
{
	char	**paths;
	int		i;

	i = 0;
	paths = get_paths(g_env);
	return (pipes(n, head, paths, g_env));
}

int	run_command(t_cmd_list *cmdline, t_g_env *g_env)
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

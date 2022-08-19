/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/19 15:27:53 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer_helper(int in, int out, int d, int n)
{
	if (in != 0)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != 1)
	{
		if (d == n - 1)
			close(out);
		else
		{
			dup2(out, 1);
			close(out);
		}
	}
}

int	executer(char ***commands, int n, t_cmd_elem *cmdline, t_exec *var)
{
	pid_t		pid;
	int			i;
	static int	d;

	i = 0;
	pid = -60;
	if (builtins(commands[d]) && n == 1)
		run_builtins(commands[d], var->g_env);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			return (error_handler(\
						"minishell: fork: Ressource temporarily unavailable", 1));
		}
		else if (pid == 0)
		{
			executer_helper(var->in, var->out, d, n);
			// you need to check builtins g_exit_status
			if (builtins(commands[d]))
				exit(run_builtins(commands[d], var->g_env));
			else
				child(cmdline, commands[d], var->g_env->env, var->paths);
		}
	}
	d++;
	if (d == n)
		d = 0;
	return (pid);
}

int	pipes(int n, t_cmd_elem *head, char **paths, t_env *g_env)
{
	int		i;
	pid_t	pid;
	t_exec	var;
	t_pipe	in_out;
	
	in_out.in = 0;
	i = 0;
	in_out.check = 0;
	while (i < n)
	{
		pipe(in_out.fd);
		var.g_env = g_env;
		var.paths = paths;
		var.in = in_out.in;
		var.out = in_out.fd[1];
		pid = executer(&head->args, n, head, &var);
		if (pipes_helper1(pid, in_out.in, in_out.fd, &in_out.check))
			break ;
		pipes_helper2(&head, in_out.fd, &in_out.in);
		i++;
	}
	pipes_helper3(in_out.in, n);
	return (0);
}

int	pipeline(int n,	t_cmd_elem *head,	t_env *g_env)
{
	char	**paths;

	paths = get_paths();
	return (pipes(n, head, paths, g_env));
}

int	run_command(t_cmd_list *cmdline, t_env *g_env)
{
	int			i;
	t_cmd_elem	*ptr;
	(void)g_env;

	i = 0;
	ptr = cmdline->head;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	ptr = cmdline->head;
	pipeline(i, cmdline->head, g_env);
	return (0);
}

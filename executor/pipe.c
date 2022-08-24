/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 16:13:40 by aboudoun         ###   ########.fr       */
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

int	executer(char **commands, int n, int i, t_cmd_elem *cmdline, t_exec *var)
{
	int	old_stdout;
	int	old_stdin;
	int	pid;

	old_stdout = dup(STDOUT_FILENO);
	old_stdin = dup(STDIN_FILENO);
	if (builtins(commands) && n == 1)
	{
		run_builtins(cmdline, commands, var->g_env);
		dup2(old_stdout, STDOUT_FILENO);
		dup2(old_stdout, STDIN_FILENO);
		close(old_stdout);
		close(old_stdin);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			error_handler("fork error\n", 2);
		else if (pid == 0)
		{
			executer_helper(var->in, var->out, i, n);
			if (builtins(commands))
				exit(run_builtins(cmdline, commands, var->g_env));
			else
				child(cmdline, commands, var->g_env, var->paths);
		}
	}
	return (0);
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
		pid = executer(head->args, n, i, head, &var);
		if (pipes_helper1(pid, in_out.in, in_out.fd, &in_out.check))
			break ;
		pipes_helper2(&head, in_out.fd, &in_out.in);
		i++;
	}
	pipes_helper3(in_out.in, n);
	i = 0;
	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
	}
	free(paths);
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

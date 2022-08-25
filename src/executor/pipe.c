/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/25 16:29:27 by yaskour          ###   ########.fr       */
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

void	builtins_body(char **commands, t_cmd_elem *cmdline, t_exec *var)
{
	int	old_stdout;
	int	old_stdin;

	old_stdout = dup(STDOUT_FILENO);
	old_stdin = dup(STDIN_FILENO);
	run_builtins(cmdline, commands, var->g_env);
	dup2(old_stdout, STDOUT_FILENO);
	dup2(old_stdout, STDIN_FILENO);
	close(old_stdout);
	close(old_stdin);
}

int	executer(char **commands, int n, int i, t_cmd_elem *cmdline, t_exec *var)
{
	int	pid;

	pid = 0;
	if (builtins(commands) && n == 1)
		builtins_body(commands, cmdline, var);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			error_handler("fork error\n", 2);
			return (-1);
		}
		else if (pid == 0)
		{
			executer_helper(var->in, var->out, i, n);
			if (builtins(commands))
				exit(run_builtins(cmdline, commands, var->g_env));
			else
				child(cmdline, commands, var->g_env, var->paths);
		}
	}
	return (pid);
}

void	end_pipes(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
	}
	free(paths);
}

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

int	pipes(int n, t_cmd_elem *head, char **paths, t_env *g_env)
{
	int			i;
	pid_t		pid;
	t_exec		var;
	t_pipe		in_out;
	int			status;
	t_cmd_elem	*ptr;

	init_out_check(&in_out, &i);
	ptr = head;
	while (i < n)
	{
		init_var(&in_out, &var, g_env, paths);
		pid = executer(ptr->args, n, i, ptr, &var);
		if (pipes_helper1(pid, in_out.in, in_out.fd, &in_out.check))
			break ;
		pipes_helper2(&ptr, in_out.fd, &in_out.in);
		i++;
	}
	if (builtins(head->args) && n == 1)
		pipes_helper3(in_out.in, n);
	else
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
		pipes_helper3(in_out.in, n);
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

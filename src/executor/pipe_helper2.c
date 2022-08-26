/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:59:14 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/26 11:35:22 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	max_len(char *str, char *str1)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str);
	len2 = ft_strlen(str1);
	if (len1 > len2)
		return (len1);
	return (len2);
}

void	executer_helper(t_exec *var, int d, int n)
{
	if (var->in == 0)
		close(var->close_first);
	if (var->in != 0)
	{
		dup2(var->in, 0);
		close(var->in);
	}
	if (var->out != 1)
	{
		if (d == n - 1)
		{	
			close(var->close_first);
			close(var->out);
		}
		else
		{
			close(var->close_first);
			dup2(var->out, 1);
			close(var->out);
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

int	executer(int n, int i, t_cmd_elem *cmdline, t_exec *var)
{
	int		pid;
	char	**commands;

	commands = cmdline->args;
	pid = 0;
	if (builtins(commands) && n == 1)
		builtins_body(commands, cmdline, var);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			if (var->out != 1)
				close(var->out);
			if (var->in != 0)
				close(var->in);
			error_handler("fork error\n", 2);
			return (-1);
		}
		else if (pid == 0)
		{
			executer_helper(var, i, n);
			if (builtins(commands))
				exit(run_builtins(cmdline, commands, var->g_env));
			else
				child(cmdline, commands, var->g_env, var->paths);
		}
	}
	return (pid);
}

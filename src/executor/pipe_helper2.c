/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:59:14 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/25 16:04:58 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int max_len(char *str,char *str1)
{
	int len1;
	int len2;

	len1 = ft_strlen(str);
	len2 = ft_strlen(str1);
	if (len1 > len2)
		return (len1);
	return (len2);
}

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
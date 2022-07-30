/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/30 13:31:12 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	executer(int in, int out, char ***commands, char **paths, \
	char **env, int n, t_env *g_env,t_cmd_elem *cmdline)
{
	pid_t		pid;
	int			i;
	char		*cmd;
	static int	d;
	(void)g_env;
	i = 0;
	pid = fork();
	if (pid == -1)
	{
		write(2, "minishell: fork: Ressource temporarily unavailable\n", 51);
		return (-1);
	}
	else if (pid == 0)
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
		redirections(cmdline,0,1);
		if (commands[d][0][0] == '/')
		{
			if (!access(commands[d][0], F_OK))
				execve(commands[d][0], commands[d], env);
			else
				write(2, "command not found\n", 18);
			exit(0);
		}
		if (builtins(commands[d]) == 1)
		{
			run_builtins(commands[d], g_env);
			exit(1);
		}
		else
		{
			while (paths[i])
			{
				cmd = ft_strjoin(paths[i], commands[d][0]);
				if (!access(cmd, F_OK))
				{
					execve(cmd, commands[d], env);
				}
				free(cmd);
				i++;
			}
			write(2, "command not found\n", 18);
			exit(1);
		}
	}
	d++;
	if (d == n)
		d = 0;
	return (pid);
}

char	***delete_spaces(t_cmd_elem *head, int n)
{
	int		i;
	char	***commands;
	int		n_of_arg;
	int		s;
	int		j;

	commands = malloc(sizeof(char **) * n + 1);
	s = 0;
	while (head)
	{
		n_of_arg = 0;
		i = 0;
		while (head->args[i])
		{
			if (ft_strncmp(head->args[i], " ", 1))
				n_of_arg++;
			i++;
		}
		commands[s] = malloc(sizeof(char *) * n_of_arg + 1);
		i = 0;
		j = 0;
		while (head->args[i])
		{
			if (ft_strncmp(head->args[i], " ", 1))
				commands[s][j++] = ft_strdup(head->args[i]);
			i++;
		}
		commands[s][j] = NULL;
		head = head->next;
		s++;
	}
	commands[s] = NULL;
	return (commands);
}

int	pipes(int n, t_cmd_elem *head, char **paths, char **env, t_env *g_env)
{
	int		in;
	int		i;
	int		fd[2];
	pid_t	pid;
	//char	*cmd;
	int		check;
	char	***commands;

	in = 0;
	i = 0;
	check = 0;
	commands = delete_spaces(head, n);
	while (i < n)
	{
		pipe(fd);
		pid = executer(in, fd[1], commands, paths, env, n, g_env,head);
		if (pid == -1)
		{
			check = 1;
			close(in);
			close(fd[0]);
			close(fd[1]);
			break ;
		}
		head = head->next;
		close(fd[1]);
		if (in != 0)
			close(in);
		in = fd[0];
		i++;
	}
	if (in != 0)
		close(in);
/*	waitpid(pid, 0, 0);
	pid = fork();
	if (!check && (pid == -1))
	{
		check = 1;
		write(2, "minishell: fork: Ressource temporarily unavailable\n", 51);
		return (-1);
	}
	else if (!check && (pid == 0))
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		redirections(head,0,1);
		if (builtins(commands[n -1]) == 1)
		{
			run_builtins(commands[n -1], g_env);
			exit(0);
		}
		else
		{
			i = 0;
			while (paths[i])
			{
				cmd = ft_strjoin(paths[i], commands[n - 1][0]);
				if (!access(cmd, F_OK))
				{
					execve(cmd, commands[n - 1], env);
				}
				free(cmd);
				i++;
			}
			write(2, "command not found\n", 18);
			exit(1);
		}
	}*/
	i = 0;
	while (i++ < n)
		wait(NULL);
	//close(in);
	return (0);
}

int	pipeline(int n,	t_cmd_elem *head,	char **env,	t_env *g_env)
{
	char **paths;

	paths = get_paths(env);
	return (pipes(n, head, paths, env, g_env));
}

int	run_command(t_cmd_list *cmdline, char **env, t_env *g_env)
{
	t_cmd_elem	*ptr;
	int			i;

	i = 0;
	ptr = cmdline->head;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	if (i == 1)
		simple_cmd(cmdline->head, env, g_env);
	if (i > 1)
		pipeline(i, cmdline->head, env, g_env);
	return (0);
}

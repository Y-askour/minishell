/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/02 15:23:49 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	executer(int in, int out, char ***commands, char **paths, \
	int n, t_env *g_env, t_cmd_elem *cmdline)
{
	pid_t		pid;
	int			i;
	static int	d;

	i = 0;
	pid = fork();
	if (pid == -1)
		return (error_handler(\
					"minishell: fork: Ressource temporarily unavailable\n"));
	else if (pid == 0)
	{
		executer_helper(in, out, d, n);
		redirections(cmdline, 0, 1);
		if (builtins(commands[d]) == 1)
			exit(run_builtins(commands[d], g_env));
		else
			child(cmdline, commands[d], g_env->env, paths);
	}
	d++;
	if (d == n)
		d = 0;
	return (pid);
}

void	delete_spaces_helper1(t_cmd_elem *head, int *i, int *n_of_arg)
{
	while (head->args[*i])
	{
		if (ft_strncmp(head->args[*i], " ", 1))
			*n_of_arg += 1;
		*i += 1;
	}
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
		delete_spaces_helper1(head, &i, &n_of_arg);
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

int	pipes_helper1(int pid, int in, int *fd, int *check)
{
	if (pid == -1)
	{
		*check = 1;
		close(in);
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	return (0);
}

void	pipes_helper2(t_cmd_elem **head, int *fd, int in)
{
	*head = (*head)->next;
	close(fd[1]);
	if (in != 0)
		close(in);
	in = fd[0];
}

void	pipes_helper3(int in, int n)
{
	int	i;

	if (in != 0)
		close(in);
	i = 0;
	while (i++ < n)
		wait(NULL);
}

int	pipes(int n, t_cmd_elem *head, char **paths, t_env *g_env)
{
	int		in;
	int		i;
	int		fd[2];
	pid_t	pid;
	int		check;
	char	***commands;

	in = 0;
	i = 0;
	check = 0;
	commands = delete_spaces(head, n);
	while (i < n)
	{
		pipe(fd);
		pid = executer(in, fd[1], commands, paths, n, g_env, head);
		if (pipes_helper1(pid, in, fd, &check))
			break ;
		pipes_helper2(&head, fd, in);
		i++;
	}
	pipes_helper3(in, n);
	return (0);
}

int	pipeline(int n,	t_cmd_elem *head,	t_env *g_env)
{
	char	**paths;

	paths = get_paths(g_env->env);
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
	if (i == 1)
		simple_cmd(cmdline->head, g_env);
	if (i > 1)
		pipeline(i, cmdline->head, g_env);
	return (0);
}

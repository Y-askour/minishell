/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:29 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/25 11:59:17 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

void	pipes_helper2(t_cmd_elem **head, int *fd, int *in)
{
	*head = (*head)->next;
	close(fd[1]);
	if (*in != 0)
		close(*in);
	*in = fd[0];
}

void	pipes_helper3(int in, int n)
{
	int	i;

	if (in != 0)
		close(in);
	i = 0;
	while (i++ < n - 1)
	{
		wait(NULL);
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
		i = -1;
		j = 0;
		while (head->args[++i])
		{
			if (ft_strncmp(head->args[i], " ",max_len(head->args[i]," ")))
				commands[s][j++] = ft_strdup(head->args[i]);
		}
		helper(commands, &head, &s, j);
	}
	commands[s] = NULL;
	return (commands);
}

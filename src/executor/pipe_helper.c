/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 15:59:29 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/26 11:10:45 by yaskour          ###   ########.fr       */
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/31 12:22:17 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	red_in(t_red_elem *red, int in)
{	
	int	f1;

	f1 = open(red->file, O_RDONLY);
	if (f1 < 0)
	{
		printf("failed to open the file\n");
		return (-1);
	}
	dup2(f1, in);
	close(f1);
	return (0);
}

int	red_out(t_red_elem *red, int out)
{
	int	f1;

	f1 = open(red->file, O_CREAT | O_WRONLY, 0666);
	if (f1 < 0)
	{
		printf("failed to open the file\n");
		return (-1);
	}
	dup2(f1, out);
	close(f1);
	return (0);
}

int	red_append(t_red_elem *red, int out)
{
	int	f1;

	f1 = open(red->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (f1 < 0)
	{
		printf("failed to open the file\n");
		return (-1);
	}
	dup2(f1, out);
	close(f1);
	return (0);
}

int	redirections(t_cmd_elem *cmd_line, int in, int out)
{
	t_cmd_elem	*temp;
	t_red_elem	*red;

	temp = cmd_line;
	red = temp->redir->head;
	while (red)
	{
		if (red->type == REDOUT)
			return (red_out(red, out));
		if (red->type == REDIN)
			return (red_in(red, in));
		if (red->type == APPEND)
			return (red_append(red, out));
		red = red->next;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/15 20:23:28 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	red_in(t_red_elem *red, int in)
{	
	// check no such file
	//int	f1;
	(void)in;

	printf("%s\n",red->file);
	/*f1 = open(red->file, O_RDONLY);
	if (f1 < 0)
	{
		printf("failed to open the file\n");
		return (-1);
	}
	dup2(f1, in);
	close(f1);*/
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
	red = cmd_line->redir->head;
	(void)in;
	(void)out;
	while (red)
	{
		if (red->type == REDOUT)
			return (red_out(red, out));
		else if (red->type == REDIN)
			return (red_in(red, in));
		else if (red->type == APPEND)
			return (red_append(red, out));
		red = red->next;
	}
	return (0);
}

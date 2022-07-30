/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/30 13:16:21 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int redirections(t_cmd_elem *cmd_line,int in,int out)
{
	t_cmd_elem *temp;
	t_red_elem *red;
	int f1;
	//int f2;
	(void)in;
	
	temp = cmd_line;
	red = temp->redir->head;
	while(red)
	{
		if (red->type == REDOUT)
		{
			f1 = open(red->file,O_CREAT|O_WRONLY,0666);
			if (f1 < 0)
			{
				printf("failed to open the file\n");
				return (-1);
			}
			dup2(f1,out);
			close(f1);
		}
		if (red->type == REDIN)
		{
			f1 = open(red->file,O_RDONLY);
			if (f1 < 0)
			{
				printf("failed to open the file\n");
				return (-1);
			}
			dup2(f1,in);
			close(f1);

		}
		if (red->type == APPEND)
		{
			f1 = open(red->file,O_CREAT|O_APPEND|O_RDWR,0666);
			if (f1 < 0)
			{
				printf("failed to open the file\n");
				return (-1);
			}
			dup2(f1,out);
			close(f1);
		}
		red = red->next;
	}
	return (0);
}

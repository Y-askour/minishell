/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/16 19:31:23 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"
int ft_is_number(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	red_in(t_red_elem *red, int in)
{	
	int	f1;

	if (ft_is_number(red->file))
		f1 = ft_atoi(red->file);
	else
	{
		f1 = open(red->file, O_RDONLY);
		if (f1 < 0)
		{
			exit_status = 1;
			error_handler("minishell: path : No such  file or directory\n");
			return (-1);
		}
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
		exit_status = 1;
		error_handler("minishell: path : No such  file or directory\n");
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
		exit_status = 1;
		error_handler("minishell: path : No such  file or directory\n");
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

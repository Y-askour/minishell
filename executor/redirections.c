/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/22 14:47:26 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

int	red_in(t_red_elem *red, int in,int check)
{	
	int	f1;
	(void)check;

	if (ft_is_number(red->file))
		f1 = ft_atoi(red->file);
	else
	{
		f1 = open(red->file, O_RDONLY);
		if (f1 < 0)
		{
			error_handler("minishell: path : No such  file or directory", 1);
			return (-1);
		}
	}
	dup2(f1, in);
	close(f1);
	return (0);
}

int	red_out(t_red_elem *red, int out,int check)
{
	int	f1;
	//old_stdout = dup(out);
	(void) check;

	f1 = open(red->file, O_CREAT | O_WRONLY, 0666);
	if (f1 < 0)
	{
		error_handler("minishell: path : No such  file or directory", 1);
		return (-1);
	}
	dup2(f1, out);
	close(f1);
	//if (check)
	//{
	//	dup2(old_stdout,STDOUT_FILENO);
	//	close(old_stdout);
	//}
	//else
	//	close(old_stdout);
	return (0);
}

int	red_append(t_red_elem *red, int out,int check)
{
	int	f1;
	(void)check;

	f1 = open(red->file, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (f1 < 0)
	{
		error_handler("minishell: path : No such  file or directory", 1);
		return (-1);
	}
	dup2(f1, out);
	close(f1);
	return (0);
}


int	redirections(t_cmd_elem *cmd_line, int in, int out,int check)
{
	t_cmd_elem	*temp;
	t_red_elem	*red;

	temp = cmd_line;
	red = cmd_line->redir->head;
	while (red)
	{
		if (red->type == REDOUT)
			red_out(red, out,check);
		else if (red->type == REDIN)
			red_in(red, in,check);
		else if (red->type == APPEND)
			red_append(red, out,check);
		red = red->next;
	}
	return (0);
}

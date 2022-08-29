/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/29 14:06:34 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	red_in(t_red_elem *red, int in)
{	
	int	f1;

	if (ft_is_number(red->file) && red->type == HEREDOC)
		f1 = ft_atoi(red->file);
	else
	{
		if (access(red->file, F_OK))
		{
			error_handler("minishell: path : No such  file or directory", 1);
			g_exit_status = 1;
			return (-1);
		}
		f1 = open(red->file, O_RDONLY);
	}
	dup2(f1, in);
	close(f1);
	return (0);
}

int	red_out(t_red_elem *red, int out)
{
	int	f1;

	if (!access(red->file, F_OK))
		unlink(red->file);
	f1 = open(red->file, O_CREAT | O_WRONLY, 0666);
	if (f1 < 0)
	{
		error_handler("minishell: path : No such  file or directory", 1);
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
		error_handler("minishell: path : No such  file or directory", 1);
		return (-1);
	}
	dup2(f1, out);
	close(f1);
	return (0);
}

int	run_redirections(t_cmd_elem *cmd_line, int in, int out)
{
	t_cmd_elem	*temp;
	t_red_elem	*red;

	temp = cmd_line;
	red = cmd_line->redir->head;
	while (red)
	{
		if (red->type == REDOUT)
		{
			if (red_out(red, out) == -1)
				return (-1);
		}
		else if (red->type == REDIN || red->type == HEREDOC)
		{
			if (red_in(red, in) == -1)
				return (-1);
		}
		else if (red->type == APPEND)
		{
			if (red_append(red, out))
				return (-1);
		}
		red = red->next;
	}
	return (0);
}

int	redirections(t_cmd_elem *cmd_line, int in, int out)
{
	t_cmd_elem	*temp;
	t_red_elem	*red;

	temp = cmd_line;
	red = cmd_line->redir->head;
	return (run_redirections(cmd_line, in, out));
}

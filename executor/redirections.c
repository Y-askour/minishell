/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 14:07:48 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/15 15:27:07 by yaskour          ###   ########.fr       */
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

//void	is_heredoc(t_red_elem *red)
//{
//	char *input;
//	input = 0;
//}

int	red_heredoc(t_red_elem *red)
{
	char *input;
	int		fd;

	input = readline(">");
	fd = open("garbage",O_CREAT|O_RDWR|O_APPEND,0666);
	if (fd < 0)
		return (-1);
	while(ft_strncmp(input, red->file, ft_strlen(red->file) + 1))
	{
		ft_putstr_fd(input,fd);
		input = readline(">");
		rl_on_new_line();
	}
	return(0);
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
		else if (red->type == REDIN)
			return (red_in(red, in));
		else if (red->type == APPEND)
			return (red_append(red, out));
		else if (red->type == HEREDOC)
			return(red_heredoc(red));
		red = red->next;
	}
	return (0);
}

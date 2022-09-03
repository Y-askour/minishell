/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/03 11:23:38 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	rl_on_new_line();Tell the update routines that we have 
	moved onto a new (empty) line, usually after ouputting a newline.
	rl_redisplay();Change what's displayed on 
	the screen to reflect the current contents of rl_line_buffer
	SIGINT;ctrl + c
	SIGQUIT, ctrl + '\'
	SIGTSTP,  ctrl + z
*/

#include"minishell.h"

static int	all_wspaces(char *line)
{
	int	i;

	i = 0;
	while (ft_strchr(" \t\r\f\v", line[i]))
	{
		i++;
		if (line[i] == '\0')
			return (1);
	}
	return (0);
}

void	signal_handler(int signal)
{
	(void) signal;
	g_exit_status = 1;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

char	*display_prompt(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell$>";
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	line = readline(prompt);
	if (!line)
	{
		write(1, "exit\n", 5);
		exit(g_exit_status);		
	}
	else if (!(*line) || all_wspaces(line))
	{
		free(line);
		return(NULL);
	}
	else
		add_history(line);
	rl_on_new_line();
	return (line);
}

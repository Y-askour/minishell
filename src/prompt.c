/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/31 17:39:43 by aboudoun         ###   ########.fr       */
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

void	signal_handler(int signal)
{
	(void) signal;
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
	if (*line)
		add_history(line);
	rl_on_new_line();
	return (line);
}

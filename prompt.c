/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/23 14:07:50 by aboudoun         ###   ########.fr       */
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
	signal(SIGTSTP, SIG_IGN);
	line = readline(prompt);
	if (!line)
	{
		printf("%s\n", "exit");
		exit(1);
	}
	if (line)
		add_history(line);
	rl_on_new_line();
	return (line);
}

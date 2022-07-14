/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/27 16:01:25 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_handler(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_replace_line(" ", 1);
	rl_on_new_line();//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
	rl_redisplay();//Change what's displayed on the screen to reflect the current contents of rl_line_buffer
}

char    *display_prompt()
{
	char    *line;
	char    *prompt;

	prompt = "minishell$>";

	signal(SIGINT, signal_handler); //ctrl + c
	signal(SIGQUIT, SIG_IGN); //ctrl + '\'
	signal(SIGTSTP, SIG_IGN); //ctrl + z
	line = readline(prompt);
	if (!line)
	{
		printf("%s", "exit");
		exit(1);
	}
	if (line)
		add_history(line);//to save the line away in a history list of such lines
	rl_on_new_line();
	return (line);
}

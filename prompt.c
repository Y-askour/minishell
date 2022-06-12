/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/12 14:06:47 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

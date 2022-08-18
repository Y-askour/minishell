/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:05 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/18 11:57:46 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_handler(int signal)
{
	//printf("\n%d\n",signal);
	(void) signal;
	rl_replace_line("", 1);
	write(1, "\n", 1);
	rl_on_new_line();/*Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.*/
	rl_redisplay();/*Change what's displayed on the screen to reflect the current contents of rl_line_buffer*/
}

char	*display_prompt(void)
{
	char	*line;
	char	*prompt;

	prompt = "minishell$>";
	signal(SIGINT, signal_handler);/*ctrl + c*/
	signal(SIGQUIT, SIG_IGN); /*ctrl + '\'*/
	signal(SIGTSTP, SIG_IGN); /*ctrl + z*/
	line = readline(prompt);
	if (!line)
	{
		printf("%s\n", "exit");
		exit(1);
	}
	if (line)
		add_history(line);/*to save the line away in a history list of such lines*/
	rl_on_new_line();
	return (line);
}

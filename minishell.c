/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/04 13:36:47 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	*prompt;

	(void) ac;
	(void) av;
	(void) env;
	prompt = "minishell$>";
	while (1)
	{
		signal(SIGINT, signal_handler); //ctrl + c
		signal(SIGQUIT, SIG_IGN); //ctrl + '\'
		signal(SIGTSTP, SIG_IGN); //ctrl + z
		line = readline(prompt);
		if (!line || !ft_strncmp(line, "exit", 4))
		{
			printf("%s", "exit");
			exit(1);
		}
		if (line)
			add_history(line);//to save the line away in a history list of such lines
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/12 14:10:39 by yaskour          ###   ########.fr       */

#include"minishell.h"

int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		check_syntax(tokens);
		
		if (!ft_strncmp(line, "exit", 4))
		{
			printf("%s", "exit");
			exit(1);
		}
	}
}

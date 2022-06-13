/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/13 22:36:56 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	//t_env *shell_env;
	// shell_env = get_env(env);
	// while(shell_env)
	// {
	// 	printf("%s = %s\n",shell_env->name,shell_env->value);
	// 	shell_env = shell_env->next;
	// }
	
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		//print_list(tokens);
		//printf("\n-------after------\n\n");
		check_syntax(tokens);
		expand(tokens, env);
		print_list(tokens);
		if (!ft_strncmp(line, "exit", 4))
		{
			printf("%s", "exit");
			exit(1);
		}
	}
}

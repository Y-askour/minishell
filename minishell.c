/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/13 17:37:38 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int exit_status = 0;


int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;
	//t_env *shell_env;
	//t_env *shell_free;
	t_cmd_list		*cmd_line = NULL;

	(void) av;
	if (ac != 1 || !*env)
		return (1);

	//shell_env = get_env(env);
	//shell_free = shell_env;
	// while(shell_env)
	// {
	// 	printf("%s = %s\n",shell_env->name,shell_env->value);
	// 	shell_env = shell_env->next;
	// }


	// shell_env = shell_free;
	// 
	// while (shell_env)
	// {
	//	 free(shell_env->name);
	//	 free(shell_env->value);
	//	 shell_free = shell_env;
	//	 shell_env = shell_env->next;
	//	 free(shell_free);
	// }
	
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		if (!check_syntax(tokens))
		{
			expand(tokens, env);
			cmd_line = parse_cmd(tokens, cmd_line);
		 	//run_command(line,shell_env,env);
		//	print_cmdline(cmd_line);
			free_cmd(cmd_line);
			//print_list(tokens);
		}
		print_list(tokens);
		free_tokens(tokens);
		free(line);
	}
}

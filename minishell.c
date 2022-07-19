/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/19 10:34:27 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

FILE *fPtr;
int exit_status = 0;

char **get_paths(char **env)
{
	t_env *shell_env; 
	t_env *ptr;
	char **paths;
	char **ret;
	int i;

	// get env
	ptr = get_env(env);
	shell_env = ptr;
	while(shell_env)
	{
		 if (!ft_strncmp(shell_env->name,"PATH",4))
			 break;
		shell_env = shell_env->next;
	}

	// split PATHS
	paths = ft_split(shell_env->value,':');
	
	// free env
	while(ptr)
	{
		free(ptr->name);
		free(ptr->value);
		shell_env = ptr;
		ptr = ptr->next;
		free(shell_env);
	}

	//add slash at the end of the paths
	i = 0;
	while(paths[i])
		i++;
	ret = malloc(sizeof(char *) * i +1);
	i = 0;
	while(paths[i])
	{
		ret[i] = ft_strjoin(paths[i],"/");
		i++;
	}
	ret[i] = NULL;
	return (ret);
}


int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;
	t_cmd_list		*cmd_line = NULL;


	(void) av;
	if (ac != 1 || !*env)
		return (1);	
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		if (!check_syntax(tokens))
		{
			expand(tokens, env);
			cmd_line = parse_cmd(tokens, cmd_line);
			run_command(cmd_line,env);
			print_cmdline(cmd_line);
		}
		//print_list(tokens);
		free_tokens(tokens);
		free_cmd(cmd_line);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/12 16:01:20 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


void	expand(t_token_list *list)
{
	t_token_elem	*temp;

	temp = list->head;
	while(temp)
	{
		// if (temp->type == WORD && temp->next)
		// {
		// 	if (temp->next->type == WORD)
		// 	{	
		// 		temp->value = ft_strjoin(temp->value, temp->next->value);
		// 		del_node(temp->next);
		// 	}
		// }
		/* I aded &&temp-> because it segf in case of temp->next == NULL*/
		//else if (temp->type == DOLLAR && temp->next)
		temp = temp->next;
	}
}
int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;
	t_env *shell_env;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	shell_env = get_env(env);
	//while(shell_env->next)
	//{
	//	printf("%s%30s\n",shell_env->name,shell_env->value);
	//	shell_env = shell_env->next;
	//}
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		//print_list(tokens);
		//printf("\n-------after------\n\n");
		//check_syntax(tokens);
		expand(tokens);
		print_list(tokens);
		if (!ft_strncmp(line, "exit", 4))
		{
			printf("%s", "exit");
			exit(1);
		}
	}
}

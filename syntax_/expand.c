/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:55:45 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/14 17:56:03 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *env_var(char *var, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (!ft_strncmp(var, tmp->name, ft_strlen(var) + 1))
            return (tmp->value);
        tmp = tmp->next;
    }
    return (" ");
}

void	expand(t_token_list *list, char **var)
{
	t_token_elem	*temp;
    t_env *env;
    
    env = get_env(var);
	temp = list->head;
	while(temp)
	{
		if (temp->type == DOLLAR && temp->next)
		{
			
			if (temp->next->type == WORD)
			{
                temp->next->value = env_var(temp->next->value, env);
				del_node(temp, list);
			}
		}
        else if (temp->type == TILDE)
        {
            temp->value = env_var("HOME", env);
        }
        temp = temp->next;
		/* I aded &&temp-> because it segf in case of temp->next == NULL*/
		//else if (temp->type == DOLLAR && temp->next)
	}
}
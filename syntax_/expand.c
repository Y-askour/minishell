/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:55:45 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/26 16:45:36 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    free_env(t_env *env)
{
    while(env)
    {
        free(env->name);
        free(env->value);
        free(env);
        env = env->next;
    }
}

char *env_var(char *var, t_env *env)
{
    t_env *tmp;

    tmp = env;
    while (tmp)
    {
        if (ft_isdigit(var[0]))
        {
            // if (var[0] == '0')
            //     return(ft_strjoin("minishell", (var + 1)));
            return(ft_strndup(var + 1, (int)ft_strlen(var + 1) + 1));
        }
        if (!ft_strncmp(var, tmp->name, ft_strlen(var) + 1))
            return (ft_strndup((tmp->value), (int)ft_strlen(tmp->value) + 1));
        tmp = tmp->next;
    }
    return (ft_strndup(" ",1));
}

void	expand(t_token_list *list, char **var)
{
	t_token_elem	*temp;
    t_env *env;
    t_env   *tmp;
    char *tofree;
    
    tmp = get_env(var);
    env = tmp;
	temp = list->head;
	while(temp)
	{
		if (temp->type == DOLLAR && temp->next)
		{
			if (temp->next->type == AFDOLLAR)
			{
                tofree = temp->next->value;
                temp->next->value = env_var(temp->next->value, env);
                free(tofree);
			    del_node(temp, list);
			}
		}
        else if (temp->type == TILDE)
        {
            if ((!temp->next && temp->prev->type == WHSPACE) || (!temp->prev && temp->next->type == WHSPACE) || 
                    (temp->next->type == WHSPACE && temp->prev->type == WHSPACE))
                temp->value = env_var("HOME", env);
        }
        /* how can you get tmp next after delleting the temp node*/
        temp = temp->next;
		/* I aded &&temp-> because it segf in case of temp->next == NULL*/
		//else if (temp->type == DOLLAR && temp->next)
	}
    free_env(tmp);
}

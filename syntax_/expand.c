/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:55:45 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/18 11:50:29 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
/*
void	free_env(t_env *env)
{
	while (env)
	{
		free(env->name);
		free(env->value);
		free(env);
		env = env->next;
	}
}*/

char	*env_var(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_isdigit(var[0]))
			return (ft_strndup(var + 1, (int)ft_strlen(var + 1) + 1));
		if (!ft_strncmp(var, tmp->name, ft_strlen(var) + 1))
			return (ft_strndup((tmp->value), (int)ft_strlen(tmp->value) + 1));
		tmp = tmp->next;
	}
	return (ft_strndup(" ", 1));
}

static void	expand_tilde(t_token_elem *temp, t_env *env)
{
	if ((!temp->next && temp->prev->type == WHSPACE) \
			|| (!temp->prev && temp->next->type == WHSPACE) \
			|| (temp->next->type == WHSPACE && temp->prev->type == WHSPACE))
		temp->value = env_var("HOME", env);
}

void	expand(t_token_list *list, t_env **g_env)
{
	t_token_elem	*temp;
	t_env			*env;
	char			*tofree;

	env = *g_env;
	temp = list->head;
	while (temp)
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
		else if (temp->type == EXITS)
			temp->value = ft_itoa(g_exit_status);
		else if (temp->type == TILDE)
			expand_tilde(temp, env);
		temp = temp->next;
	}
}

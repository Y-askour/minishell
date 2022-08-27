/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:55:45 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/27 15:41:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*env_var(char *var, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_isdigit(var[0]))
		{
			if (var[0] == '0')
				return (ft_strjoin(ft_strdup("minishell"), \
						ft_strdup((var + 1))));
			return (ft_strndup(var + 1, (int)ft_strlen(var + 1) + 1));
		}
		if (!ft_strncmp(var, tmp->name, max_len(var, tmp->name)))
			return (ft_strndup((tmp->value), (int)ft_strlen(tmp->value) + 1));
		tmp = tmp->next;
	}
	return (ft_strdup(""));
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
			temp->value = env_var("HOME", env);
		temp = temp->next;
	}
}

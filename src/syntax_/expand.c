/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 17:55:45 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/28 15:40:08 by aboudoun         ###   ########.fr       */
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

static void	join_tild(t_token_elem *temp, t_token_list *list)
{
	while (temp->next && temp->next->type == WORD)
	{
		temp->value = ft_strjoin(ft_strdup(temp->value), \
			ft_strdup(temp->next->value));
		del_node(temp->next, list);
	}
}

static void	expand_tild(t_token_elem *temp, t_env *env, t_token_list *list)
{
	char	*tofree;

	if (temp->type == TILDE)
		join_tild(temp, list);
	if ((!ft_strncmp("~", temp->value, max_len("~", temp->value)) && \
		temp->type != TILDE))
	{
		tofree = temp->value;
		temp->value = env_var("HOME", env);
		free(tofree);
	}
	else if (!ft_strncmp("~/", temp->value, 2))
	{
		tofree = temp->value;
		temp->value = ft_strjoin(env_var("HOME", env), \
			ft_strdup((temp->value + 1)));
		free(tofree);
	}
}

void	expand_exit(t_token_elem *temp)
{
	char	*tofree;

	tofree = temp->value;
	temp->value = ft_itoa(g_exit_status);
	free(tofree);
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
			expand_exit(temp);
		else
			expand_tild(temp, env, list);
		temp = temp->next;
	}
}

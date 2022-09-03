/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:27:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/03 14:18:40 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**lst_to_arr(t_env *g_env)
{
	char	**env;
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = g_env;
	while (ptr)
	{
		if (ptr->value)
			i++;
		ptr = ptr->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	ptr = g_env;
	i = 0;
	while (ptr)
	{
		if (ptr->value)
		{
			env[i] = ft_strjoin(ft_strjoin(ft_strdup(ptr->name), \
					ft_strdup("=")), ft_strdup(ptr->value));
			i++;
		}
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

int	env_search(t_g_env *g_env, char *name, char *value)
{
	t_env	*env;

	env = g_env->head;
	while (env)
	{		
		if (!ft_strncmp(env->name, name, max_len(env->name, name)))
		{
			free(name);
			free(env->value);
			if (!value)
			{
				free(value);
				env->value = ft_strdup("");
			}
			else
				env->value = value;
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_env_helper(t_g_env *g_env, char **split)
{
	t_env	*node;
	t_env	*tmp;

	node = malloc(sizeof(t_env) * 1);
	node->name = ft_strndup(split[0], ft_strlen(split[0]));
	free(split[0]);
	node->next = NULL;
	tmp = g_env->head;
	if (!split[1])
	{
		free(split[1]);
		node->value = ft_strdup("");
	}
	else
		node->value = split[1];
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

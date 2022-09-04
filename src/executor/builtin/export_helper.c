/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 19:27:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/04 21:19:06 by yaskour          ###   ########.fr       */
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
		i++;
		ptr = ptr->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	ptr = g_env;
	i = 0;
	while (ptr)
	{
		env[i] = ft_strjoin(ft_strjoin(ft_strdup(ptr->name), \
					ft_strdup("=")), ft_strdup(ptr->value));
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
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

int	add_env_2(char **split, t_g_env *g_env)
{
	if (!g_env->head)
	{
		g_env->head = malloc(sizeof(t_env) * 1);
		g_env->head->name = ft_strndup(split[0], ft_strlen(split[0]));
		free(split[0]);
		if (split[1])
			g_env->head->value = split[1];
		else
		{
			g_env->head->value = ft_strdup("");
			free(split[1]);
		}
		g_env->head->next = NULL;
		free(split);
		return (1);
	}
	return (0);
}

void	add_env_1(char **split, t_g_env *g_env)
{
	t_env	*tmp;

	tmp = g_env->head;
	if (add_env_2(split, g_env))
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, split[0], \
				max_len(tmp->name, split[0]) - 1))
		{
			free(split[0]);
			if (split[1])
			{
				tmp->value = ft_strjoin(tmp->value, split[1]);
			}
			else
				free(split[1]);
			free(split);
			return ;
		}
		tmp = tmp->next;
	}
	add_env_helper(g_env, split);
	free(split);
	return ;
}

int	check_to_add(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	**split_env(char *to_split, char sp)
{
	char	**splited;
	int		i;

	i = 0;
	splited = NULL;
	while (to_split[i])
	{
		if (to_split[i] == sp)
			break ;
		i++;
	}
	splited = malloc(sizeof(char) * 2);
	if (!to_split[i])
	{
		splited[0] = to_split;
		splited[1] = ft_strdup("");
	}
	else
	{
		splited[0] = ft_strndup(to_split, i + 1);
		splited[1] = ft_strdup(&to_split[i + 1]);
	}
	return (splited);
}

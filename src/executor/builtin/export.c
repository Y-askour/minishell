/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/26 19:28:50 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	add_env_1(char **split, t_env *g_env)
{
	t_env	*tmp;

	tmp = g_env;
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

void	add_env2(char **split, t_env *node, t_env **g_env)
{
	if (!split[1])
	{
		node->value = ft_strdup("");
		free(split[1]);
	}
	else
		node->value = split[1];
	free(split);
	while ((*g_env)->next)
		*g_env = (*g_env)->next;
}

void	add_env(char *command, t_env *g_env)
{
	int		i;
	char	**split;
	t_env	*node;
	t_env	*tmp;

	tmp = g_env;
	i = 0;
	split = ft_split(command, '=');
	if (split[0][ft_strlen(split[0]) - 1] == '+')
		return (add_env_1(split, g_env));
	else if (env_search(g_env, split[0], split[1]))
		return (free(split));
	node = malloc(sizeof(t_env) * 1);
	node->env = g_env->env;
	node->name = split[0];
	node->next = NULL;
	add_env2(split, node, &g_env);
	g_env->next = node;
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

int	export_f(char **command, t_env *env)
{
	int	i;

	i = 0;
	count_and_declare(&i, command, env);
	if (i >= 2)
	{
		i = 1;
		while (command[i])
		{
			if (option(command[1]))
			{
				error_handler("minishell : export : invalid option", 1);
				return (-1);
			}
			else if (valid(command[i]))
			{
				add_env(command[i], env);
			}
			else
				error_handler("minishell: export: `=` \
						:not a valid indentifier", 1);
			i++;
		}
	}
	return (0);
}

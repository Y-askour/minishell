/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/31 15:52:41 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env_1(char **split, t_g_env *g_env)
{
	t_env	*tmp;

	tmp = g_env->head;
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

void	add_env2(char **split, t_env *node)
{
	if (!split[1])
	{
		node->value = ft_strdup("");
		free(split[1]);
	}
	else
		node->value = split[1];
	free(split);
}

void	add_env(char *command, t_g_env *g_env)
{
	int		i;
	char	**split;
	t_env	*node;
	t_env	*tmp;

	tmp = g_env->head;	
	i = 0;
	split = ft_split(command, '=');
	if (split[0][ft_strlen(split[0]) - 1] == '+')
		return (add_env_1(split, g_env));
	else if (env_search(g_env, split[0], split[1]))
		return (free(split));
	node = malloc(sizeof(t_env) * 1);
	node->name = split[0];
	node->next = NULL;
	add_env2(split, node);
	tmp = g_env->head;
	if (!tmp)
	{
		g_env->head = node;
		return;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = node;
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

void	add_null_value(char *command, t_g_env *env)
{
	t_env	*head;
	t_env	*node;
	t_env	*prev;
	int		i;

	head = env->head;
	prev = env->head;
	i = 0;
	while (head)
	{
		if (!ft_strncmp(command,head->name,max_len(command,head->name)))
			return ;
		if (i > 0)
			prev = prev->next;
		head = head->next;
		i++;
	}
	node = malloc(sizeof(t_env)* 1);
	node->name = command;
	node->value = NULL;
	node->next = NULL;
	prev->next = node;
}

int	export_f(char **command, t_g_env *env)
{
	int	i;

	i = 0;
	printf("head -> %p\n",env->head);
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
				if (check_to_add(command[i]))
					add_env(command[i], env);
				else
					add_null_value(command[i],env);
			}
			else
				error_handler("minishell: export: `=` \
						:not a valid indentifier", 1);
			i++;
		}
	}
	return (0);
}

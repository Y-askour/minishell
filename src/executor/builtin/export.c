/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/01 12:56:44 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**split_env(char	*to_split, char	sp)
{
	char	**splited;
	int		i;

	i = 0;
	splited = NULL;
	while(to_split[i])
	{
		if (to_split[i] == sp)
			break;
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
	splited[0] = ft_strndup(to_split,i + 1);
	splited[1] = ft_strdup(&to_split[i + 1]);
	}
	return (splited);
}

int	search_env(char	*name,char	*value,t_g_env	*g_env)
{
	t_env	*ptr;
	ptr = g_env->head;
	while(ptr)
	{
		if (!ft_strncmp(name,ptr->name,max_len(name,ptr->name)))
		{
			free(name);
			if (ptr->value)
				free(ptr->value);
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

void add_env(char *command, t_g_env *g_env)
{
	char	**splited;
	t_env	*env;
	t_env	*node;

	env = g_env->head;
	splited = split_env(command, '=');
	if (!search_env(splited[0],splited[1],g_env))
	{
		node = malloc(sizeof(t_env)* 1);
		node->name = splited[0];
		node->value = splited[1];
		node->next = NULL;
		if (!env)
			g_env->head = node;
		else
		{
			while(env->next)
				env = env->next;
			env->next = node;
		}
	}
	free(splited);
}

int	export_f(char **command, t_g_env *env)
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
				if (check_to_add(command[i]))
					add_env(command[i], env);
			//	else
			//		add_null_value(command[i],env);
			}
			else
				error_handler("minishell: export: `=` \
						:not a valid indentifier", 1);
			i++;
		}
	}
	return (0);
}

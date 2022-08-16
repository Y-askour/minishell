/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:03 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/03 13:41:15 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../include/minishell.h"

void	declare_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

void	check_f(char *command, int *check)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_isalpha(command[i]) || command[i++] == '_')
	{
		while(command[i])
		{
			if (ft_isalnum(command[i]) || command[i] == '_')
			i++;
		}
		*check = 1;
	}
}

int	search_in_exp(t_env **env, char **split)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->name, split[0], ft_strlen(temp->name)))
		{
			//free(temp->value);
			if (!split[1])
				temp->value = "";
			else
				temp->value = split[1];
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_env_node(char **split, t_env **env)
{
	t_env		*node;
	t_env		*temp;

	node = malloc(sizeof(t_env) * 1);
	node->name = split[0];
	if (!split[1])
		node->value = " ";
	else
		node->value = split[1];
	node->next = NULL;
	temp = *env;
	while (temp->next)
		temp = temp->next;
	temp->next = node;
}

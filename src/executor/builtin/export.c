/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/05 11:17:09 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	add_env(char *command, t_g_env *g_env)
{
	char	**splited;
	t_env	*env;
	t_env	*node;

	env = g_env->head;
	splited = split_env(command, '=');
	if (splited[0][ft_strlen(splited[0]) - 1] == '+')
		return (add_env_1(splited, g_env));
	if (!search_env(splited[0], splited[1], g_env))
	{
		node = malloc(sizeof(t_env) * 1);
		node->name = splited[0];
		node->value = splited[1];
		node->next = NULL;
		if (!env)
			g_env->head = node;
		else
		{
			while (env->next)
				env = env->next;
			env->next = node;
		}
	}
	free(splited);
}

int	add_null_value_helper(t_g_env *env, char *command)
{
	if (!env->head)
	{
		env->head = malloc(sizeof(t_env) * 1);
		env->head->name = ft_strdup(command);
		env->head->value = NULL;
		env->head->next = NULL;
		return (1);
	}
	return (0);
}

void	add_null_value(char *command, t_g_env *env)
{
	t_env	*head;
	t_env	*node;

	head = env->head;
	if (add_null_value_helper(env, command))
		return ;
	while (head)
	{
		if (!ft_strncmp(command, head->name, max_len(command, head->name)))
			return ;
		head = head->next;
	}
	node = malloc(sizeof(t_env) * 1);
	node->name = ft_strdup(command);
	node->value = NULL;
	node->next = NULL;
	head = env->head;
	while (head->next)
		head = head->next;
	head->next = node;
}

int	while_export_f(char	**command, int *i, t_g_env *env)
{
	while (command[*i])
	{
		if (option(command[1]))
		{
			error_handler("minishell : export : invalid option", 1);
			return (-1);
		}
		else if (valid(command[*i]))
		{
			if (check_to_add(command[*i]))
				add_env(command[*i], env);
			else
				add_null_value(command[*i], env);
		}
		else
			error_handler("minishell: export : invalid indentifier", 1);
		*i = *i + 1;
	}
	return (0);
}

int	export_f(char **command, t_g_env *env)
{
	int	i;

	i = 0;
	count_and_declare(&i, command, env);
	if (i >= 2)
	{
		i = 1;
		if (while_export_f(command, &i, env) == -1)
			return (-1);
	}
	return (0);
}

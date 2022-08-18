/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/17 14:23:13 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_and_declare(int *i, char **command, t_env *env)
{
	while (command[*i])
		*i += 1;
	if (*i == 1)
		declare_export(env);
}

int	option(char *str)
{
	int i;

	i = 0;
	if (str[i] && str[i] == '-' && str[i + 1])
		return (1);
	return (0);
}

int valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i++] == '_')
	{
		while(str[i])
		{
			if (!ft_isalnum(str[i]) || !(str[i] == '-'))
				return (1);
			i++;
		}
	}
	return (0);
}

void	add_env(char *command,t_env *env)
{
	int	i;
	char **split;
	t_env	*node;
	
	i = 0;
	split = ft_split(command,'=');
	node = malloc(sizeof(t_env) * 1);
	node->env = env->env;
	node->name = split[0];
	if (!split[1])
		node->value = " ";
	else
		node->value = split[1];
	while(env->next)
		env = env->next;
	env->next = node; 
}

int check_to_add(char *command)
{
	int	i;

	i = 0;
	while(command[i])
	{
		if (command[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_f(char **command, t_env *env)
{
	int		i;
	//int		check;
	//char	**split;

	i = 0;
	count_and_declare(&i, command, env);
	if (i >= 2)
	{
		i = 1;
		while (command[i])
		{
			if (option(command[i]))
			{
				error_handler("minishell : export : invalid option", 1);
			}
			else if (valid(command[i]))
			{
				if (check_to_add(command[i]))
					add_env(command[i],env);
			}
			else
				error_handler("minishell: export: `=` :not a valid indentifier", 1);
			i++;
		}
	}
	return (0);
}

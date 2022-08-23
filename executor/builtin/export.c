/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/23 17:04:55 by yaskour          ###   ########.fr       */
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
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while(str[i])
		{
			if (str[i] == '=')
				break ;
			else if (!ft_isalnum(str[i]) && !(str[i] == '=') && !(str[i] == '_'))
			{
				if (str[i] == '+' && str[i + 1])
				{
					if (!(str[i + 1] == '='))
						return (0);
				}
				else
					return (0);
			}
			if (i == ((int)ft_strlen(str) - 1) )
				return (1);
			i++;
		}
		return (1);
	}
	return (0);
}

char **lst_to_arr(t_env *g_env)
{
	char **env;
	t_env	*ptr;
	int i;

	i = 0;
	ptr = g_env;
	while(ptr)
	{
		i++;
		ptr = ptr->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	ptr = g_env;
	i = 0;
	while(ptr)
	{
		env[i] = ft_strjoin(ft_strjoin(ft_strdup(ptr->name),ft_strdup("=")),ft_strdup(ptr->value)); 
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}
int  env_search(t_env *env,char *name,char *value)
{
	while(env)
	{
		if (!ft_strncmp(env->name,name,ft_strlen(name)))
		{
			if (!value)
				env->value = " ";
			else
				env->value = value; 
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_env(char *command,t_env *g_env)
{
	int	i;
	char **split;
	t_env	*node;
	t_env	*tmp;
	

	tmp = g_env;
	i = 0;
	split = ft_split(command,'=');
	if (split[0][ft_strlen(split[0]) -1] == '+')
	{
		while(tmp)
		{
			if (!ft_strncmp(tmp->name,split[0],ft_strlen(split[0]) - 1))
			{
				if (split[1])
					tmp->value = ft_strjoin(ft_strdup(tmp->value),ft_strdup(split[1]));
				return ;
			}
			tmp = tmp->next;
		}
		node = malloc(sizeof(t_env) * 1);
		node->env = g_env->env;
		node->name = ft_strndup(split[0],ft_strlen(split[0]));
		node->next = NULL;
		tmp = g_env;
		if (!split[1])
			node->value = " ";
		else
			node->value = split[1];
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = node; 
		return;
	}
	if (env_search(g_env,split[0],split[1]))
		return ;
	node = malloc(sizeof(t_env) * 1);
	node->env = g_env->env;
	node->name = split[0];
	node->next = NULL;
	if (!split[1])
		node->value = " ";
	else
		node->value = split[1];
	while(g_env->next)
		g_env = g_env->next;
	g_env->next = node; 
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

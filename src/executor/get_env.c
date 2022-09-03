/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:15:51 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/03 16:14:27 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_end(t_g_env *my_env, char *name, char *value)
{
	t_env	*ptr;
	t_env	*tmp;

	ptr = my_env->head;
	tmp = malloc(sizeof(t_env));
	tmp->name = name;
	tmp->value = value;
	tmp->next = NULL;
	if (!my_env->head)
	{
		my_env->head = tmp;
		return ;
	}
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = tmp;
}

void	get_env_loop(char **env,	t_g_env *my_env)
{
	char	*tmp;
	int		i;
	char	**splited;

	i = 0;
	while (env[i])
	{
		splited = split_env(env[i], '=');
		if (!ft_strncmp(splited[0], "SHLVL", max_len(splited[0], "SHLVL")))
		{
			tmp = ft_itoa(ft_atoi(splited[1]) + 1);
			free(splited[1]);
			splited[1] = tmp;
		}
		add_at_end(my_env, splited[0], splited[1]);
		free(splited);
		i++;
	}
}

t_g_env	*get_env_helper(char **env)
{
	t_g_env	*my_env;

	my_env = malloc(sizeof(t_g_env) * 1);
	my_env->head = NULL;
	get_env_loop(env, my_env);
	return (my_env);
}

t_g_env	*get_env(char **env)
{
	char	*pwd;

	pwd = NULL;
	if (!*env)
	{
		pwd = malloc(sizeof(char) * PATH_MAX);
		getcwd(pwd, PATH_MAX);
		env[0] = ft_strjoin(ft_strjoin(ft_strdup("PWD"), ft_strdup("=")), pwd);
		env[1] = ft_strdup("SHLVL=0");
		env[2] = NULL;
	}
	return (get_env_helper(env));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:15:51 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 20:19:23 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_at_end(t_env *my_env, char *name, char *value, char **env)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	tmp->name = name;
	tmp->value = value;
	tmp->env = env;
	tmp->next = NULL;
	while (my_env->next)
		my_env = my_env->next;
	my_env->next = tmp;
}

t_env	*get_env(char **env)
{
	int		i;
	t_env	*my_env;
	char	**splited;
	char	*tmp;
	char	*pwd;

	my_env = NULL;
	i = 0;
	pwd = NULL;
	if (!*env)
	{
		pwd = malloc(sizeof(char) * PATH_MAX);
		getcwd(pwd, PATH_MAX);
		env[0] = ft_strdup("SHLVL=1");
		env[1] = ft_strjoin(ft_strjoin(ft_strdup("PWD"), ft_strdup("=")), pwd);
		env[2] = NULL;
	}
	splited = ft_split(env[i], '=');
	my_env = malloc(sizeof(t_env) * 1);
	my_env->env = env;
	my_env->name = splited[0];
	my_env->value = splited[1];
	my_env->next = NULL;
	free(splited);
	i++;
	while (env[i])
	{
		splited = ft_split(env[i], '=');
		if (!ft_strncmp(splited[0], "SHLVL", max_len(splited[0], "SHLVL")))
		{
			tmp = ft_itoa(ft_atoi(splited[1]) + 1);
			free(splited[1]);
			splited[1] = tmp;
		}
		add_at_end(my_env, splited[0], splited[1], env);
		free(splited);
		i++;
	}
	return (my_env);
}

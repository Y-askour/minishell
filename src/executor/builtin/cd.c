/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/29 14:12:49 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_oldpwd(t_env *env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	tmp = env;
	prev = env;
	i = 0;
	while (tmp)
	{
		if (i > 1)
			prev = prev->next;
		if (!ft_strncmp(tmp->name, "OLDPWD", max_len(tmp->name, "OLDPWD")))
			break ;
		tmp = tmp->next;
		i++;
	}
	prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	cd_switch_change(t_env *env, t_env *old)
{
	t_env	*tmp;
	char	*swap;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", max_len(tmp->name, "PWD")))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		delete_oldpwd(env);
		return ;
	}
	swap = tmp->value;
	tmp->value = old->value;
	old->value = swap;
}

void	cd_switch(t_env *env)
{
	t_env	*tmp;
	t_env	*old;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "OLDPWD", max_len(tmp->name, "OLDPWD")))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error_handler("minishell: cd: OLDPWD not set", 1);
		return ;
	}
	chdir(tmp->value);
	printf("%s \n", tmp->value);
	old = tmp;
	cd_switch_change(env, old);
}

void	cd(char **command, t_env *env)
{
	char	*pwd;
	char	*old_pwd;

	if (!command[1])
		cd_only(env);
	else if (!ft_strncmp(command[1], "-", max_len(command[1], "-")))
		cd_switch(env);
	else
	{
		pwd = malloc(sizeof(char) * 255);
		old_pwd = malloc(sizeof(char) * 255);
		getcwd(old_pwd, PATH_MAX);
		if (!access(command[1], F_OK))
			cd_to(&pwd, &old_pwd, command, env);
		else
		{
			free(pwd);
			free(old_pwd);
			error_handler("cd : path: No such file or directory", 1);
			return ;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/27 19:33:39 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_only(t_env	*env)
{
	char	*home;
	t_env	*tmp;
	t_env	*tmp1;
	t_env	*node;

	tmp = env;
	node = NULL;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "HOME", max_len(tmp->name, "HOME")))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error_handler("minishell : cd: HOME not set", 1);
		return ;
	}
	home = tmp->value;
	chdir(tmp->value);
	tmp = env;
	tmp1 = env;
	cd_only_helper(tmp, tmp1, node, home);
}

void	cd_switch(t_env *env)
{
	char	*old_pwd;
	t_env	*tmp;

	old_pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(old_pwd, PATH_MAX);
	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "OLDPWD", max_len(tmp->name, "OLDPWD")))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error_handler("minishell : cd: not set", 1);
		return ;
	}
	chdir(tmp->value);
	printf("%s\n", tmp->value);
	free(tmp->value);
	tmp->value = old_pwd;
	tmp = env;
}

void	cd_to(char **pwd, char **old_pwd, char **command, t_env *env)
{
	t_env		*tmp;
	t_env		*node;

	node = NULL;
	if (cd_to_check(command) && ft_strncmp(command[1],"..",max_len(command[1],"..")))
	{
		free(*pwd);
		free(*old_pwd);
		return ;
	}
	chdir(command[1]);
	tmp = env;
	while (tmp)
	{
		if (!strncmp(tmp->name, "PWD", 3))
		{
			free(*pwd);
			free(*old_pwd);
			*pwd = malloc(sizeof(char) * 255);
			getcwd(*pwd, PATH_MAX);
			free(tmp->value);
			tmp->value = *pwd;
			break ;
		}
		tmp = tmp->next;
	}
	//cd_to_helper(env, node, tmp, *old_pwd);
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
			return;
		}
	}
}

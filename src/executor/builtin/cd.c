/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/28 15:10:48 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (!tmp)
	{
		free(*pwd);
		free(*old_pwd);
		return;
	}
}

void	cd_only_change_pwd(t_env *env)
{
	t_env	*tmp;
	char	*pwd;

	tmp = env;
	while(tmp)
	{
		if (!ft_strncmp(tmp->name,"PWD",max_len(tmp->name,"PWD")))
			break;
		tmp = tmp->next;
	}
	if (!tmp)
		return;
	free(tmp->value);
	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd,PATH_MAX);
	tmp->value = pwd;
}

void	cd_only(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while(tmp)
	{
		if (!ft_strncmp(tmp->name,"HOME",max_len(tmp->name,"HOME")))
			break;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error_handler("minishell : cd: HOME not set", 1);
		return;
	}
	chdir(tmp->value);
	cd_only_change_pwd(env);
}

void	delete_oldpwd(t_env *env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	tmp = env;
	prev = env;
	i = 0;
	while(tmp)
	{
		if (i > 1)
			prev = prev->next;
		if (!ft_strncmp(tmp->name,"OLDPWD",max_len(tmp->name,"OLDPWD")))
			break;
		tmp = tmp->next;
		i++;
	}
	prev->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
}

void	cd_switch_change(t_env *env,t_env *old)
{
	t_env	*tmp;
	char	*swap;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name,"PWD",max_len(tmp->name,"PWD")))
			break;
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
	while(tmp)
	{
		if (!ft_strncmp(tmp->name,"OLDPWD",max_len(tmp->name,"OLDPWD")))
			break;
		tmp = tmp->next;
	}
	if (!tmp)
	{
		error_handler("minishell: cd: OLDPWD not set",1);
		return;
	}
	chdir(tmp->value);
	printf("%s \n",tmp->value);
	old = tmp;
	cd_switch_change(env,old);
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

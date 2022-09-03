/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:19:17 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/03 13:05:46 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_to_check(char **command)
{
	struct stat	finfo;

	lstat(command[1], &finfo);
	if (!S_ISDIR(finfo.st_mode))
	{
		error_handler("cd : path: is not directory", 126);
		return (1);
	}
	if (access(command[1], X_OK))
	{
		error_handler("cd : path: Permission denied", 126);
		return (1);
	}
	return (0);
}

int	cd_to_free(t_env *tmp, char **pwd, char **old_pwd)
{
	if (!tmp)
	{
		free(*pwd);
		free(*old_pwd);
		return (1);
	}
	return (0);
}

void	cd_to(char **pwd, char **old_pwd, char **command, t_g_env *env)
{
	t_env		*tmp;
	t_env		*node;

	node = NULL;
	if (check_path(command, pwd, old_pwd))
		return ;
	if (chdir(command[1]) == -1)
		return;
	if (errno == ENOENT)
		error_handler("error azaml",1);
	tmp = env->head;
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
	cd_to_free(tmp, pwd, old_pwd);
}

void	cd_only_change_pwd(t_g_env *env)
{
	t_env	*tmp;
	char	*pwd;

	tmp = env->head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", max_len(tmp->name, "PWD")))
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	free(tmp->value);
	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd, PATH_MAX);
	tmp->value = pwd;
}

void	cd_only(t_g_env *env)
{
	t_env	*tmp;

	tmp = env->head;
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
	if (chdir(tmp->value) == -1)
		return;
	cd_only_change_pwd(env);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:19:17 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/04 20:55:07 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd_to_check(char **command)
{
	struct stat	finfo;

	lstat(command[1], &finfo);
	if (!S_ISDIR(finfo.st_mode))
	{
		error_handler("cd : is not directory", 126);
		return (1);
	}
	if (access(command[1], X_OK))
	{
		error_handler("cd : Permission denied", 126);
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
	chdir(command[1]);
	if (errno == ENOENT)
		error_handler("cd: error retrieving current directory: getcwd: \
cannot access parent directories: No such file or directory", 1);
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
		return ;
	cd_only_change_pwd(env);
}

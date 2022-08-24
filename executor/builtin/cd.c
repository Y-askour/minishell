/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 19:31:09 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **command, t_env *env)
{
	char	*pwd;
	t_env *tmp;
	char	*home;
	char	*old_pwd;
	t_env	*node;
	struct stat	finfo;


	tmp = env;
	if (!command[1])
	{
		while(tmp)
		{
			if (!ft_strncmp(tmp->name,"HOME",max_len(tmp->name,"HOME")))
				break;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			error_handler("minishell : cd: HOME not set",1);
			return;
		}
		home = tmp->value;
		chdir(tmp->value);
		tmp = env;
		while (tmp)
		{
			if (!strncmp(tmp->name, "PWD", 3))
			{
				free(tmp->value);
				tmp->value = ft_strdup(home);
				break ;
			}
			tmp = tmp->next;
		}
	}
	else if (!ft_strncmp(command[1],"-",max_len(command[1],"-")))
	{
		old_pwd = malloc(sizeof(char) * PATH_MAX);
		pwd = malloc(sizeof(char) * PATH_MAX);
		getcwd(old_pwd,PATH_MAX);
		tmp = env;
		while(tmp)
		{
			if (!ft_strncmp(tmp->name,"OLDPWD",max_len(tmp->name,"OLDPWD")))
				break;
			tmp = tmp->next;
		}
		if (!tmp)
		{
			error_handler("minishell : cd: not set",1);
			return;
		}
		chdir(tmp->value);
		tmp->value = old_pwd; 
		tmp = env;
		while(tmp)
		{
			if (!ft_strncmp(tmp->name,"PWD",max_len(tmp->name,"PWD")))
				break;
			tmp = tmp->next;
		}
		getcwd(pwd,PATH_MAX);
		tmp->value = pwd;

	}
	else
	{
		pwd = malloc(sizeof(char) * 255);
		old_pwd = malloc(sizeof(char) * 255);
		getcwd(old_pwd, PATH_MAX);
		if (!access(command[1], F_OK))
		{
			lstat(command[1], &finfo);
			if (!S_ISDIR(finfo.st_mode))
			{
				error_handler("cd : path: is not directory", 126);
				return;
			}
			if (access(command[1], X_OK))
			{
				error_handler("cd : path: Permission denied", 126);
				return;
			}
			chdir(command[1]);
			tmp = env;
			while (tmp)
			{
				if (!strncmp(tmp->name, "PWD", 3))
				{
					getcwd(pwd, PATH_MAX);
					tmp->value = pwd;
					break ;
				}
				tmp = tmp->next;
			}
			tmp = env;
			while (tmp)
			{
				if (!strncmp(tmp->name, "OLDPWD", 6))
				{
					free(tmp->value);
					tmp->value = old_pwd;
					break ;
				}
				tmp = tmp->next;
			}
			if (!tmp)
			{
				node = malloc(sizeof(t_env) * 1);
				node->name = "OLDPWD";
				node->value = old_pwd;
				node->next = NULL;
				tmp = env;
				while(tmp->next)
					tmp = tmp->next;
				tmp->next = node;
			}
		}
		else
		{
			error_handler("cd : path: No such file or directory", 127);
			return ;
		}
		g_exit_status = 0;
	}
}

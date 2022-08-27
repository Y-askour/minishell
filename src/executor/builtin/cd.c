/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/27 18:20:33 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_path(t_env *env)
{
	t_env		*node;
	t_env		*tmp;
	char		*pwd;

	node = env;
	while (node)
	{
		if (!ft_strncmp(node->name, "PWD", max_len(node->name, "PWD")))
			break ;
		node = node->next;
	}
	if (!node)
	{
		tmp = malloc(sizeof(t_env));
		pwd = malloc(PATH_MAX);
		getcwd(pwd, PATH_MAX);
		env->next = tmp;
		tmp->name = "PWD";
		tmp->value = pwd;
		tmp->next = NULL;
	}
}

void	cd_only(t_env	*env)
{
	char	*home;
	t_env	*tmp;
	t_env	*tmp1;
	t_env	*node;
	int		i;

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
	i = 0;
	while (tmp)
	{
		if (i > 0)
			tmp1 = tmp1->next;
		if (!strncmp(tmp->name, "PWD", max_len(tmp->name, "PWD")))
		{
			free(tmp->value);
			tmp->value = ft_strdup(home);
			return ;
		}
		i++;
		tmp = tmp->next;
	}
	if (!tmp1->next)
	{
		printf("%s\n", tmp1->name);
		printf("test\n");
		node = malloc(sizeof(t_env) * 1);
		tmp1->next = node;
		node->name = ft_strdup("PWD");
		node->value = ft_strdup(home);
		node->next = NULL;
	}
}

void	cd_switch(t_env *env)
{
	char	*pwd;
	char	*old_pwd;
	t_env	*tmp;

	old_pwd = malloc(sizeof(char) * PATH_MAX);
	pwd = malloc(sizeof(char) * PATH_MAX);
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
	tmp->value = old_pwd;
	tmp = env;
	cd_path(env);
}

void	cd_to(char **pwd, char **old_pwd, char **command, t_env *env)
{
	t_env		*tmp;
	t_env		*node;

	node = NULL;
	cd_to_check(command);
	chdir(command[1]);
	tmp = env;
	while (tmp)
	{
		if (!strncmp(tmp->name, "PWD", 3))
		{
			getcwd(*pwd, PATH_MAX);
			tmp->value = *pwd;
			break ;
		}
		tmp = tmp->next;
	}
	cd_to_helper(env, node, tmp, *old_pwd);
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
			return ((void)error_handler(
					"cd : path: No such file or directory", 1));
	}
}

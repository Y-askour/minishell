/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:19:17 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/27 19:31:57 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_to_helper(t_env *env, t_env *node, t_env *tmp, char *old_pwd)
{
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
		node->name = ft_strdup("OLDPWD");
		node->value = ft_strdup(old_pwd);
		node->next = NULL;
		tmp = env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
}

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

void	cd_only_helper(t_env *tmp, t_env *tmp1, t_env *node, char *home)
{
	int		i;

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
		node = malloc(sizeof(t_env) * 1);
		tmp1->next = node;
		node->name = ft_strdup("PWD");
		node->value = home;
		node->next = NULL;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:44:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/28 17:30:17 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_path(char **command, char **pwd, char **old_pwd)
{
	if (cd_to_check(command) && ft_strncmp(command[1], "..",
			max_len(command[1], "..")))
	{
		free(*pwd);
		free(*old_pwd);
		return (1);
	}
	return (1);
}

void	path_search_helper(char **command, int **check, char **env)
{
	char	*path;
	char	*cmd;

	if (command[0][1] != '/')
	{
		error_handler("minishell: path : command not found", 127);
		exit(127);
	}
	else
	{
		path = malloc(sizeof(char) * PATH_MAX);
		getcwd(path, PATH_MAX);
		cmd = ft_strjoin(ft_strdup(path), ft_strdup(&command[0][1]));
		free(path);
		if (!check_dir(cmd, 0))
		{
			**check = 1;
			execve(cmd, command, env);
		}
	}
}

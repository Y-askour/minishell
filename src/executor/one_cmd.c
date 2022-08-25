/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:16 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/25 12:24:00 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dir(char *cmd, int check)
{
	struct stat	finfo;

	if (!access(cmd, F_OK))
	{
		lstat(cmd, &finfo);
		if (S_ISDIR(finfo.st_mode))
		{
			error_handler("minishell : path: is a directory", 126);
			exit(1);
		}
		if (access(cmd, X_OK))
		{
			error_handler("minishell : path: Permission denied", 126);
			exit(1);
		}
	}
	else if (check == 0)
	{
		error_handler("minishell : path: No such file or directory", 127);
		exit(1);
	}
	return (0);
}

void	path_search(char **paths, char **command, char	**env, int *check)
{
	int		i;
	char	*cmd;

	i = 0;
	if (command[0][0] == '.')
	{
		path_search_helper(command, &check, env);
		exit(1);
	}
	if (!paths)
	{
		error_handler("minishell: path : command not found", 127);
		exit(127);
	}
	while (paths[i])
	{
		cmd = ft_strjoin(ft_strdup(paths[i]), ft_strdup(command[0]));
		if (!check_dir(cmd, 1))
			execve(cmd, command, env);
		free(cmd);
		i++;
	}
	error_handler("minishell: path : command not found", 127);
	exit(127);
}

int	child(t_cmd_elem *cmdline, char **command, t_env *env, char **paths)
{
	int		check;
	int		i;
	char	**list;

	// signal(SIGINT, SIG_IGN);
	//signal(SIGQUIT, SIG_IGN);
	check = 0;
	i = 0;
	list = lst_to_arr(env);
	if (redirections(cmdline, 0, 1) == -1)
		return (-1);
	if (command[0][0] == '/')
	{
		if (!check_dir(command[0], 0))
			execve(command[0], command, list);
	}
	path_search(paths, command, list, &check);
	return (0);
}

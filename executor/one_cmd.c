/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:16 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/18 11:50:29 by aboudoun         ###   ########.fr       */
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
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], command[0]);
		if (!check_dir(cmd, 1))
		{
			//*check = 1;
			execve(cmd, command, env);
		}
		free(cmd);
		i++;
	}
	error_handler("minishell: path : command not found", 127);
	exit(127);
}

int	child(t_cmd_elem *cmdline, char **command, char **env, char **paths)
{
	int		check;
	int		i;

	check = 0;
	i = 0;
	if (redirections(cmdline, 0, 1) == -1)
		return (-1);
	if (command[0][0] == '/')
	{
		if (!check_dir(command[0], 0))
		{
			execve(command[0], command, env);	
		}
	}
	path_search(paths, command, env, &check);
	//if (check == 0)
	//	error_handler("command not found\n");
	return (0);
}

void	simple_cmd(t_cmd_elem *cmdline, t_env *g_env)
{
	char	**command;
	char	**paths;
	int		pid;
	int tmpexit;

	command = simple_cmd_delete_spc(cmdline);
	paths = get_paths();
	// you need to check builtins g_exit_status
	if (builtins(command) == 1)
		run_builtins(command, g_env);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			error_handler(\
					"minishell: fork: Ressource temporarily unavailable", 1);
			return ;
		}
		else if (pid == 0)
		{
			child(cmdline, command, g_env->env, paths);
		}
		waitpid(pid,&tmpexit, (int) NULL);
		g_exit_status = WEXITSTATUS(tmpexit);
	}
}

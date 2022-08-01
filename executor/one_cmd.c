/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:16 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/01 13:10:36 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_spc_helper(t_cmd_elem *cmdline, int *arg_n)
{
	int	i;

	i = 0;
	while (cmdline->args[i])
	{
		if (ft_strncmp(cmdline->args[i], " ", 1))
			*arg_n += 1;
		i++;
	}
}

char	**simple_cmd_delete_spc(t_cmd_elem *cmdline)
{
	int		i;
	int		arg_n;
	char	**command;

	i = 0;
	arg_n = 0;
	delete_spc_helper(cmdline, &arg_n);
	command = malloc(sizeof(char *) * arg_n + 1);
	i = 0;
	arg_n = 0;
	while (cmdline->args[i])
	{
		if (ft_strncmp(cmdline->args[i], " ", 1))
		{
			command[arg_n] = ft_strdup(cmdline->args[i]);
			arg_n++;
		}
		i++;
	}
	command[arg_n] = NULL;
	return (command);
}

void	path_search(char **paths, char **command, char	**env, int *check)
{
	int		i;
	char	*cmd;

	i = 0;
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], command[0]);
		if (!access(cmd, F_OK))
		{
			*check = 1;
			execve(cmd, command, env);
		}
		free(cmd);
		i++;
	}
	char *working_dir = malloc(sizeof(char) * PATH_MAX);
	getcwd(working_dir,PATH_MAX);
	working_dir = ft_strjoin(working_dir,"/");
	cmd = ft_strjoin(working_dir,command[0]);
	*check = 0;
	if (!access(cmd,F_OK))
	{
		struct stat finfo;
		lstat(cmd,&finfo);
		if (S_ISDIR(finfo.st_mode))
			printf("minishell : path: is a directory\n");
		// i  need to check if file is executable
		*check = 1;
		execve(cmd, command, env);
	}
}

int	child(t_cmd_elem *cmdline, char **command, char **env, char **paths)
{
	int		check;
	int		i;

	check = 0;
	i = 0;
	if (redirections(cmdline, 0, 1) == -1)
		return (-1);
	// i need to check "./______" and "____/" 
	// and "no such file or directory" "and permission denied"
	if (command[0][0] == '.')
	{
		return (-1);
		printf("test\n");
		exit(1);
	}
	//if (command[0][ft_strlen(command[0]) - 1] == '/')
	//{
	//	//char *path;
	//	//path = ft_strjoin(,);
	//	//printf("%d\n",d);
	//	//exit(1);
	//}
	if (command[0][0] == '/')
	{
		if (!access(command[0], F_OK))
			execve(command[0], command, env);
		else
			write(2, "minishell : /ls : No such file a directory\n", 43);
		exit(1);
	}
	path_search(paths, command, env, &check);
	if (check == 0)
		write(2, "command not found\n", 18);
	exit(1);
}

void	simple_cmd(t_cmd_elem *cmdline, char **env, t_env *g_env)
{
	char	**command;
	char	**paths;
	int		pid;

	command = simple_cmd_delete_spc(cmdline);
	paths = get_paths(env);
	if (builtins(command) == 1)
		run_builtins(command, g_env);
	else
	{
		pid = fork();
		if (pid == -1)
		{
			write(2, "minishell: fork: Ressource temporarily unavailable\n", 51);
			return ;
		}
		else if (pid == 0)
			child(cmdline, command, env, paths);
		waitpid(pid, (int *) NULL, (int) NULL);
	}
}

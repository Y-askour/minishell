/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:16 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/28 14:42:49 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**simple_cmd_delete_spc(t_cmd_elem *cmdline)
{
	int i = 0;
	int arg_n = 0;
	char **command;

	while (cmdline->args[i])
	{
		if (ft_strncmp(cmdline->args[i]," ",1))
			arg_n++;
		i++;
	}
	command = malloc(sizeof(char *) * arg_n + 1);
	i = 0;
	arg_n = 0;
	while (cmdline->args[i])
	{
		if (ft_strncmp(cmdline->args[i]," ",1))
		{
			command[arg_n] = ft_strdup(cmdline->args[i]);
			arg_n++;
		}
		i++;
	}
	command[arg_n] = NULL;
	return (command);
}

void simple_cmd(t_cmd_elem *cmdline,char **env,t_env *g_env)
{
	char **command;
	char **paths;
	int pid;
	char *cmd;
	int i = 0;
	int check = 0;

	command = simple_cmd_delete_spc(cmdline);
	paths = get_paths(env);

	if (builtins(command) == 1)
		run_builtins(command,g_env);
	else
	{
		if ((pid = fork() ) == -1)
		{
			write(2,"minishell: fork: Ressource temporarily unavailable\n",51);
			return ;
		}
		else if (pid == 0)
		{
			// i need to check "./______" and "____/"  and "no such file or directory" "and permission denied"
			if (command[0][0] == '/')
			{
				if (!access(command[0],F_OK))
					execve(command[0],command,env);
				else
					write(2,"minishell : /ls : No such file a directory\n",43);
			}
			else
			{
				while(paths[i])
				{
					cmd = ft_strjoin(paths[i],command[0]);
					if (!access(cmd,F_OK))
					{
						check = 1;
						execve(cmd,command,env);
					}
					free(cmd);
					i++;
				}
				if ( check == 0)
					write(2,"command not found\n",18);
			}
			exit(1);
		}
		waitpid(pid,(int *)NULL,(int)NULL);
	}
}


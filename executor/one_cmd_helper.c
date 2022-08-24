/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 14:44:22 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 19:24:06 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

void	path_search_helper(char **command, int **check, char **env)
{
	char	*path;
	char	*cmd;

	if (command[0][1] != '/')
	{
		error_handler("minishell: path : command not found", 1);
		exit(1);
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

void	delete_spc_helper(t_cmd_elem *cmdline, int *arg_n)
{
	int	i;

	i = 0;
	while (cmdline->args[i])
	{
		if (ft_strncmp(cmdline->args[i], " ", max_len(cmdline->args[i]," ")))
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
		if (ft_strncmp(cmdline->args[i], " ", max_len(cmdline->args[i]," ")))
		{
			command[arg_n] = ft_strdup(cmdline->args[i]);
			arg_n++;
		}
		i++;
	}
	command[arg_n] = NULL;
	return (command);
}

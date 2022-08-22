/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/22 18:14:08 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(t_cmd_elem *cmdline,char **command, t_env *env)
{
	if (redirections(cmdline, 0, 1) == -1)
		return (-1);
	if (!ft_strncmp(command[0], "echo", 4))
		echo(command);
	else if (!ft_strncmp(command[0], "cd", 2))
		cd(command, env);
	else if (!ft_strncmp(command[0], "pwd", 3))
		pwd(command, env);
	else if (!ft_strncmp(command[0], "export", 6))
		export_f(command, env);
	else if (!ft_strncmp(command[0], "unset", 5))
		cd(command, env);
	else if (!ft_strncmp(command[0], "env", 3))
		env_f(command, env);
	else if (!ft_strncmp(command[0], "exit", 4))
		exit_f();
	return (1);
}

int	builtins(char **command)
{
	// for redirections
	if (!command[0])
		return (0);
	if (!ft_strncmp(command[0], "echo", 4))
		return (1);
	else if (!ft_strncmp(command[0], "cd", 2))
		return (1);
	else if (!ft_strncmp(command[0], "pwd", 3))
		return (1);
	else if (!ft_strncmp(command[0], "export", 6))
		return (1);
	else if (!ft_strncmp(command[0], "unset", 5))
		return (1);
	else if (!ft_strncmp(command[0], "env", 3))
		return (1);
	else if (!ft_strncmp(command[0], "exit", 4))
		return (1);
	return (0);
}

void	env_f(char **command, t_env *env)
{
	(void)command;
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	exit_f(void)
{
	exit(1);
}

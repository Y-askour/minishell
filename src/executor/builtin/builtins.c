/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/04 13:57:58 by yaskour          ###   ########.fr       */
=======
/*   Updated: 2022/09/04 15:38:58 by yaskour          ###   ########.fr       */
>>>>>>> test
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_builtins(t_cmd_elem *cmdline, char **command, t_g_env *env)
{
	if (redirections(cmdline, 0, 1) == -1)
		return (1);
	if (!command[0])
		return (0);
	if (!ft_strncmp(command[0], "echo", max_len(command[0], "echo")))
		echo(command);
	else if (!ft_strncmp(command[0], "cd", max_len(command[0], "cd")))
		cd(command, env);
	else if (!ft_strncmp(command[0], "pwd", max_len(command[0], "pwd")))
		pwd();
	else if (!ft_strncmp(command[0], "export", max_len(command[0], "export")))
		export_f(command, env);
	else if (!ft_strncmp(command[0], "unset", max_len(command[0], "unset")))
		unset(command, env);
	else if (!ft_strncmp(command[0], "env", max_len(command[0], "env")))
		env_f(command, env);
	else if (!ft_strncmp(command[0], "exit", max_len(command[0], "exit")))
		exit_f(command);
	return (1);
}

int	builtins(char **command)
{
	if (!command[0])
		return (1);
	if (!ft_strncmp(command[0], "echo", max_len(command[0], "echo")))
		return (1);
	else if (!ft_strncmp(command[0], "cd", max_len(command[0], "cd")))
		return (1);
	else if (!ft_strncmp(command[0], "pwd", max_len(command[0], "pwd")))
		return (1);
	else if (!ft_strncmp(command[0], "export", max_len(command[0], "export")))
		return (1);
	else if (!ft_strncmp(command[0], "unset", max_len(command[0], "unset")))
		return (1);
	else if (!ft_strncmp(command[0], "env", max_len(command[0], "env")))
		return (1);
	else if (!ft_strncmp(command[0], "exit", max_len(command[0], "exit")))
		return (1);
	return (0);
}

void	env_f(char **command, t_g_env *g_env)
{
	t_env	*env;

	(void)command;
	env = g_env->head;
	while (env)
	{
		if (env->value && ft_strncmp(env->value, "", max_len(env->value, "")))
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	exit_helper(char **command)
{
	int	i;

	i = 1;
	while (command[i])
		i++;
	if (i == 2)
		exit(ft_atoi(command[1]));
	else
		error_handler("exit\nminishell : exit : too many arguments", 1);
}

void	exit_f(char **command)
{
	int	j;

	j = 0;
	if (!command[1])
	{
		write(1, "exit\n", 5);
		exit(g_exit_status);
	}
	if (command[1][j] == '+' || command[1][j] == '-')
		j++;
	while (command[1][j])
	{
		if (!ft_isdigit(command[1][j]))
		{
			error_handler("exit\nminishell: exit : numeric \
				argument required", 255);
			exit(255);
		}
		j++;
	}
	exit_helper(command);
}

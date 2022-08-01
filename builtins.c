/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/31 15:04:21 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void	run_builtins(char **command, t_env *env)
{
	if (!ft_strncmp(command[0], "echo", 4))
	{
		cd(command, env);
	}
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
}

int	builtins(char **command)
{
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

void	cd(char **command, t_env *env)
{
	char	*path;

	path = malloc(sizeof(char) * 255);
	chdir(command[1]);
	while (env)
	{
		if (!strncmp(env->name, "PWD", 3))
		{
			getcwd(path, PATH_MAX);
			env->value = path;
			break ;
		}
		env = env->next;
	}
}

void	pwd(char **command, t_env *env)
{
	char	*pwd;

	(void)command;
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
			break ;
		env = env->next;
	}
	pwd = env->value;
	printf("%s\n", pwd);
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

void declare_export(t_env *env)
{
	while(env)
	{
		printf("declare -x %s=\"%s\"\n",env->name,env->value);
		env = env->next;
	}
}

void	export_f(char **command, t_env *env)
{
	int	i;
	int j;
	int check;
	char **split;
	t_env *node;

	i = 0;
	(void) env;
	while (command[i])
		i++;
	if (i == 1)
		declare_export(env);
	else if (i >= 2 )
	{
		i = 1;
		while(command[i])
		{
			check = 0;
			j = 0;
			while(command[i][j])
			{
				if (command[i][j] == '=')
					check = 1;
				j++;
			}
			if (check)
			{
				split = ft_split(command[i],'=');
				node = malloc(sizeof(t_env) * 1);
				node->name = split[0];
				if (!split[1])
					node->value = " ";
				else
					node->value = split[1];
				node->next = NULL;
				t_env *temp = env;
				while(temp)
					temp = temp->next;
				temp->next = node;
			}
			i++;
		}
	}
		return ;
}

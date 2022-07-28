/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/28 10:50:56 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void cd(char **command,t_env *env)
{
	char *path;
	path = malloc(sizeof(char) * PATH_MAX);
	if (!command[1])
	{
		chdir("..");
		while(env)
		{
			if(!strncmp(env->name,"PWD",3))
			{
				getcwd(path,PATH_MAX);
				env->value = path;
				break;
			}
			env = env->next;
		}
	}
}

void pwd(char **command,t_env *env)
{
	char *pwd;
	(void)command;
	while(env)
	{
		if(!ft_strncmp(env->name,"PWD",3))
			break;
		env = env->next;
	}
	pwd = env->value;
	printf("%s\n",pwd);
}

void env_f(char **command,t_env *env)
{
	(void)command;
	while(env)
	{
		printf("%s=%s\n",env->name,env->value);
		env = env->next;
	}
}

void exit_f()
{
	exit(1);
}

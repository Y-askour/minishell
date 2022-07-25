/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/25 18:49:24 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>

void cd(char **command,t_env *env)
{
	(void) command;
	chdir("/bin");
	while(env)
	{
		if(!strncmp(env->name,"PWD",3))
		{
			env->value = "/bin";
			break;
		}
		env = env->next;
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 13:48:26 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/28 10:59:45 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../include/minishell.h>


void run_builtins(char **command,t_env *env)
{
	if (!ft_strncmp(command[0],"echo",4))
		cd(command,env);
	if (!ft_strncmp(command[0],"cd",2))
		cd(command,env);
	if (!ft_strncmp(command[0],"pwd",3))
		pwd(command,env);
	if (!ft_strncmp(command[0],"export",6))
		export_f(command,env);
	if (!ft_strncmp(command[0],"unset",5))
		cd(command,env);
	if (!ft_strncmp(command[0],"env",3))
		env_f(command,env);
	if (!ft_strncmp(command[0],"exit",4))
		exit_f(command,env);
}

int builtins(char **command)
{
	if (!ft_strncmp(command[0],"echo",4))
		return (1);
	if (!ft_strncmp(command[0],"cd",2))
		return (1);
	if (!ft_strncmp(command[0],"pwd",3))
		return (1);
	if (!ft_strncmp(command[0],"export",6))
		return (1);
	if (!ft_strncmp(command[0],"unset",5))
		return (1);
	if (!ft_strncmp(command[0],"env",3))
		return (1);
	if (!ft_strncmp(command[0],"exit",4))
		return (1);	
	return (0);
}

void cd(char **command,t_env *env)
{
	char *path;
	path = malloc(sizeof(char) * 255);
	chdir(command[1]);
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

void export_f(char **command,t_env *env)
{
	(void) env;
	int i = 0;
	while(command[i])
		printf("%s\n",command[i++]);
	if (i == 1)
	{
		printf("----\n");
		/// khassk thandli had lcase 
	}
	else if ( i == 2 )
		return ;	
}

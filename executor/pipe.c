/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:48:23 by yaskour           #+#    #+#             */
/*   Updated: 2022/07/15 18:24:05 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minishell.h"

int executer(int in, int out ,char ***commands, char **paths,char **env,int n)
{
	pid_t pid;
	int i = 0;
	char *cmd;
	static int d =0;
	if (( pid = fork() ) == 0)
	{
		if (in != 0)
		{
			dup2(in,0);
			close(in);
		}
		if ( out != 1 )
		{
			dup2(out,1);
			close(out);
		}

		while(paths[i])
		{
			cmd = ft_strjoin(paths[i],commands[d][0]);
			if (!access(cmd,F_OK))
			{
				execve(cmd,commands[d],env);
			}
			free(cmd);
			i++;
		}
		write(2,"command not found\n",18);
		exit(1);
	}
	d++;
	if (d == n - 1)
		d = 0;
	return (pid);
}

char	***delete_spaces(t_cmd_elem *head,int n)
{
	int i;
	char ***commands;
	int n_of_arg;
	int s;
	int j;

	commands  =  malloc(sizeof(char **) * n + 1);
	s = 0;
	while(head)
	{
		n_of_arg = 0;
		i = 0;
		while(head->args[i])
		{
			if (ft_strncmp(head->args[i]," ",1))
				n_of_arg++;
			i++;
		}
		commands[s] = malloc(sizeof(char *) * n_of_arg + 1);
		i = 0;
		j = 0;
		while(head->args[i])
		{
			if (ft_strncmp(head->args[i]," ",1))
				commands[s][j++] = ft_strdup(head->args[i]);
			i++;
		}
		commands[s][j] = NULL;
		head = head->next;
		s++;
	}
	commands[s] = NULL;
	return (commands);
}

int pipes(int n,t_cmd_elem *head,char **paths,char **env)
{

	int in;
	int i;
	int fd[2];
	pid_t pid;
	char *cmd;

	in = 0;
	i = 0;
	char ***commands = delete_spaces(head,n);
	while(i < n -1)
	{
		// all this run in parent process
		pipe(fd);
		// run command
		// this line run in child process
		pid = executer(in,fd[1],commands,paths,env,n);
		head = head->next;
		close(fd[1]);
		in = fd[0];
		waitpid(pid,(int *)NULL,(int)NULL);
		i++;
	}
	// i need to execute the last command
	if ( (pid = fork()) == 0)
	{
		if (in != 0)
			dup2(in,0);
		while(paths[i])
		{
			//you need to check invalid commands
			cmd = ft_strjoin(paths[i],commands[n - 1][0]);
			if (!access(cmd,F_OK))
			{
				//printf("%s\n",cmd);
				execve(cmd,commands[n - 1],env);
			}
			free(cmd);
			i++;
		}
		write(2,"command not found\n",18);
		exit(1);
	}
	waitpid(pid,(int *)NULL,(int)NULL);
	return (0);
}

int pipeline(int n,t_cmd_elem *head,char **env)
{
	char **paths;

	paths = get_paths(env); 
	//int i;
	//n = 0;
	//while(head)
	//{
	//	i = 0;
	//	while(head->args[i])
	//		printf("%s\n",head->args[i++]);
	//	head = head->next;
	//	printf("-----------------\n");
	//}
	pipes(n,head,paths,env);
	return (0);
}

int run_command(t_cmd_list *cmdline,char **env)
{

	t_cmd_elem *ptr;

	int i = 0;
	ptr = cmdline->head;
	while(ptr)
	{
		i++;
		ptr = ptr->next;
	}
	if (i == 1)
		simple_cmd(cmdline->head,env);
	if (i > 1)
		pipeline(i,cmdline->head,env);
	return (0);
}

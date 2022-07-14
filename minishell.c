/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/14 18:48:29 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

FILE *fPtr;
int exit_status = 0;

char **get_paths(char **env)
{
	t_env *shell_env; 
	t_env *ptr;
	char **paths;
	char **ret;
	int i;

	// get env
	ptr = get_env(env);
	shell_env = ptr;
	while(shell_env)
	{
		 if (!ft_strncmp(shell_env->name,"PATH",4))
			 break;
		shell_env = shell_env->next;
	}

	// split PATHS
	paths = ft_split(shell_env->value,':');
	
	// free env
	while(ptr)
	{
		free(ptr->name);
		free(ptr->value);
		shell_env = ptr;
		ptr = ptr->next;
		free(shell_env);
	}

	//add slash at the end of the paths
	i = 0;
	while(paths[i])
		i++;
	ret = malloc(sizeof(char *) * i +1);
	i = 0;
	while(paths[i])
	{
		ret[i] = ft_strjoin(paths[i],"/");
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int executer(int in, int out ,char **arg, char **paths,char **env)
{
	(void)arg;
	(void) in; 
	(void) out;
	(void) paths;
	pid_t pid;
	int i = 0;
	char *cmd;
	char ***commands;
	commands = malloc(sizeof(char **) * 2);
	int j = 0;
	while (j < 3)
	{
		commands[j] = malloc(sizeof(char *) * 3);
		j++;
	}
	commands[0][0] = "ls";
	commands[0][1] = NULL;
	commands[0][2] = NULL;
	
	commands[1][0] = "grep";
	commands[1][1] = "Makefile";
	commands[1][2] = NULL;

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
		exit(1);
	}
	fPtr = fopen("test", "a");
	fputs(ft_strjoin(ft_itoa(d),"\n"), fPtr);
	fPtr = freopen("test", "r", fPtr);
	fclose(fPtr);
	d++;
	if (d == 2)
		d = 0;
	//waitpid(pid,(int *)NULL,(int)NULL);



	//int j = 0;
	//while(arg[j])
	//{
	//	printf("%s\n",arg[j++]);
	//}
	//printf("-------\n");
	return (pid);
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
	while(i < n -1)
	{
		// all this run in parent process
		pipe(fd);
		// run command
		// this line run in child process
		executer(in,fd[1],head->args,paths,env);
		head = head->next;
		close(fd[1]);
		in = fd[0];
		i++;
	}
	char **commands = malloc(sizeof(char *) * 3);
	commands[0] = "wc";
	commands[1] = "-l";
	commands[2] = NULL;
	// i need to execute the last command
	if ( (pid = fork()) == 0)
	{
		if (in != 0)
			dup2(in,0);
		while(paths[i])
		{
			//you need to check invalid commands
			cmd = ft_strjoin(paths[i],commands[0]);
			if (!access(cmd,F_OK))
			{
				//printf("%s\n",cmd);
				execve(cmd,commands,env);
			}
			free(cmd);
			i++;
		}
		exit(1);
	}
	waitpid(pid,(int *)NULL,(int)NULL);
	return (0);
}

int pipeline(int n,t_cmd_elem *head,char **env)
{
	char **paths;


	paths = get_paths(env); 
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
	if (i > 1)
		pipeline(i,cmdline->head,env);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;
	t_cmd_list		*cmd_line = NULL;


	(void) av;
	if (ac != 1 || !*env)
		return (1);	
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		if (!check_syntax(tokens))
		{
			expand(tokens, env);
			cmd_line = parse_cmd(tokens, cmd_line);
			run_command(cmd_line,env);
			//print_cmdline(cmd_line);
			free_cmd(cmd_line);
		}
		//print_list(tokens);
		free_tokens(tokens);
		free(line);
	}
}

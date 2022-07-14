/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/14 15:48:38 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

int executer(int in, int out ,char **arg, char **env)
{
	(void) in; 
	(void) out;
	(void) env;



	int j = 0;
	while(arg[j])
	{
		printf("%s\n",arg[j++]);
	}
	printf("-------\n");
	return (0);
}

int pipes(int n,t_cmd_elem *head,char **paths)
{

	//int in;
	int i;
	//int fd[2];

	//in = 0;
	i = 0;
	int j;
	(void) paths;
	while(i < n -1)
	{
		j = 0;
		//pipe(fd);
		// run command
		executer(0,0,head->args,paths);
		head = head->next;
		//close(fd[1]);
		//in = fd[0];
		i++;
	}
	//if (in != 0)
	//	dup2(in,0);
	// i need to execute the last command
	return (0);
}

int pipeline(int n,t_cmd_elem *head,char **env)
{
	char **paths;


	paths = get_paths(env); 
	pipes(n,head,paths);
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

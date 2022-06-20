/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/20 17:31:24 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int check_command_type(char *line)
{
	if (!ft_strncmp(line,"echo",4))
		return(1);
	if (!ft_strncmp(line,"cd",2))
		return(1);
	if (!ft_strncmp(line,"pwd",3))
	{
		return(1);
	}
	if (!ft_strncmp(line,"export",6))
		return(1);
	if (!ft_strncmp(line,"unset",5))
		return(1);
	if (!ft_strncmp(line,"env",3))
		return(1);
	if (!ft_strncmp(line,"exit",4))
		return(1);
	return (0);
}

void run_builtin(char *line)
{
	char current_dir[PATH_MAX];

	if (!ft_strncmp(line,"echo",4))
		printf("%s\n",&line[4]);
	if (!ft_strncmp(line,"cd",2))
	{
		if (!line[2])
			chdir("/Users/yaskour");
		else
			chdir(&line[3]);
	}
	if (!ft_strncmp(line,"pwd",3))
	{
		getcwd(current_dir,sizeof(current_dir));
		printf("%s\n",current_dir);
	}
	if (!ft_strncmp(line,"export",6))
		printf("export\n");
	if (!ft_strncmp(line,"unset",5))
		printf("unset\n");
	if (!ft_strncmp(line,"env",3))
		printf("env\n");
	if (!ft_strncmp(line,"exit",4))
		exit(1);
}

void	excute_non_builtin(char *command, char **paths,char **env)
{
	int	i;

	i = 0;
	char *cmd;
	char **cmd2;
	cmd2 = ft_split(command, ' ');
	while (paths[i])
	{
		cmd = ft_strjoin(paths[i], cmd2[0]);
		if (!access(cmd, F_OK))
		{
			//printf("hani hna ya zaml\n");
			execve(cmd, cmd2,env);
		}
		free(cmd);
		i++;
	}
	exit(1);
}

void run_command(char *line,t_env *env,char **enver)
{
	// count how many commands we have
	char	**splited;
	char	**paths;
	char	**ret;
	int i;

	splited = ft_split(line,'|');
	i = 0;
	while(splited[i])
		i++;
	// if number of commands is 1 then run this part
	if (i == 1)
	{
		if (!check_command_type(line))
		{
			int id = fork();
			if (id == 0)
			{
				t_env *test;
				test = env;
				while(test)
				{
					if (!ft_strncmp(test->name,"PATH",4))
						break;
					test = test->next;
				}
				paths = ft_split(test->value,':');
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
				excute_non_builtin(line,ret,enver);
			}
			else
				wait(0);
		}
		else
			run_builtin(line);
	}
}



int	main(int ac, char **av, char **env)
{
	char    *line;
	t_token_list	*tokens;
	//t_env *shell_env;
	t_cmd_list		*cmd_line = NULL;

	(void) av;
	if (ac != 1 || !*env)
		return (1);
	//shell_env = get_env(env);
	// while(shell_env)
	// {
	// 	printf("%s = %s\n",shell_env->name,shell_env->value);
	// 	shell_env = shell_env->next;
	// }
	
	while (1)
	{
		line = display_prompt();
		tokens = lexical_analyser(line);
		//print_list(tokens);
		//printf("\n-------after------\n\n");
		// if (!check_syntax(tokens))
		// 	run_command(line,shell_env,env);
		if (!check_syntax(tokens))
		{	
			expand(tokens, env);
			//print_list(tokens);
		}
		cmd_line = parse_cmd(tokens, cmd_line);
		//print_list(tokens);
		print_cmdline(cmd_line);
		//if (!ft_strncmp(line, "exit", 4))
		//{
		//	printf("%s", "exit");
		//	exit(1);
		//}
	}
}

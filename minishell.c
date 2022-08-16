/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/16 18:42:11 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include"minishell.h"

int exit_status = 0;

char **get_paths()
{
	char	**paths;
	char	**ret;
	int		i;

	ret = 0;
	char *tmp = getenv("PATH");
	if (tmp)
	{
		paths = ft_split(tmp, ':');
		i = 0;
		while (paths[i])
			i++;
		ret = malloc(sizeof(char *) * i +1);
		i = 0;
		while (paths[i])
		{
			ret[i] = ft_strjoin(paths[i], "/");
			i++;
		}
		ret[i] = NULL;
	}
	return (ret);
}

void	shllvl(t_env *g_env)
{
	t_env	*temp;

	temp = g_env;
	while (temp)
	{
		if (!ft_strncmp(temp->name, "SHLVL", 5))
			break ;
		temp = temp->next;
	}
	temp->value = ft_itoa(ft_atoi(temp->value) + 1);
}

void	heredoc_signal(int signal)
{
	(void) signal;
	exit(1);
}

void input_heredoc(int *fd, t_token_elem *node)
{
	char	*input;

	input = readline(">");
	if  (!input)
		exit(1);
	while(ft_strncmp(input, node->next->value, ft_strlen(node->next->value) + 1))
	{
		signal(SIGINT, heredoc_signal);
		ft_putstr_fd(input,fd[1]);
		input = readline(">");
		if (!input)
			exit(1);
		rl_on_new_line();
	}
	close(fd[0]);
	close(fd[1]);
	exit(1);
}

void	is_heredoc(t_token_list *list)
{
	t_token_elem *node;
	int		fd[2];
	int		pid;
	
	node = list->head;
	while (node)
	{
		if(node->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			pipe(fd);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
				input_heredoc(fd, node);
			else
				waitpid(pid,0,0);
		close(fd[1]);
		node->type = REDIN;
		node->next->value = ft_itoa(fd[0]);
		}
		node = node->next;
	}
}

int	loop_body(char **line, t_token_list **tokens,
t_cmd_list **cmd_line, t_env **g_env)
{
	(void)	g_env;
	(void)	cmd_line;
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = lexical_analyser(*line);
	if (!check_syntax(*tokens))
	{
		is_heredoc(*tokens);
		expand(*tokens, g_env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		run_command(*cmd_line, *g_env);
		//print_cmdline(*cmd_line);
		free_cmd(*cmd_line);
	}
	return (0);
}


int	main(int ac, char **av, char **env)
{
	char			*line;
	t_token_list	*tokens;
	t_cmd_list		*cmd_line;
	t_env			*g_env;

	cmd_line = NULL;
	g_env = get_env(env);
	(void) av;
	//shllvl(g_env);
	if (ac != 1)
		return (1);
	while (1)
	{
		if (loop_body(&line, &tokens, &cmd_line, &g_env))
			continue ;
		//print_list(tokens);
		free_tokens(tokens);
		free(line);
	}
}

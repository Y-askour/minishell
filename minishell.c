/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/15 20:33:18 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char **get_paths(char **env)
{
	char	**paths;
	char	**ret;
	int		i;

	(void)env;
	paths = ft_split(getenv("PATH"), ':');
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

void	red_heredoc(t_token_list *list)
{
	t_token_elem *node;
	char *input;
	int		fd[2];

	node = list->head;
	while (node)
	{
		if(node->type == HEREDOC)
		{
			pipe(fd);
			input = readline(">");
			while(ft_strncmp(input, node->next->value, ft_strlen(node->next->value) + 1))
			{
				ft_putstr_fd(input,fd[1]);
				input = readline(">");
				rl_on_new_line();
			}
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
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = lexical_analyser(*line);
	if (!check_syntax(*tokens))
	{
		red_heredoc(*tokens);
		expand(*tokens, g_env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		run_command(*cmd_line, *g_env);
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
	shllvl(g_env);
	if (ac != 1 || !*env)
		return (1);
	while (1)
	{
		if (loop_body(&line, &tokens ,&cmd_line, &g_env))
			continue ;
		free(line);
	}
}

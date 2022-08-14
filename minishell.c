/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/14 18:07:21 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	g_exit_status = 0;

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	**get_paths(char **env)
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

static void	is_heredoc(t_token_list *tokens)
{
	t_token_elem	*tmp;
	char			*input;

	tmp = tokens->head;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
		{
			if (tmp->next && tmp->next->type == WHSPACE)
				del_node(tmp->next, tokens);
			if (!tmp->next || tmp->next->type != WORD)
			{
				tmp->value = ft_strdup("syntax error near unexpected token `newline'\n");
				tmp->type = ERROR;
				break;
			}
			int fd = open("garbage",O_CREAT|O_WRONLY,0666);
			input = readline(">");
			while (ft_strcmp(input, tmp->next->value))
			{
				ft_putstr_fd(input, fd);
				input = readline(">");
				rl_on_new_line();
			}
		}
		tmp = tmp->next;
	}
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

int	loop_body(char **line, t_token_list **tokens,
		t_cmd_list **cmd_line, t_env **g_env)
{
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = lexical_analyser(*line);
	is_heredoc(*tokens);
	if (!check_syntax(*tokens))
	{
		expand(*tokens, g_env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		run_command(*cmd_line, *g_env);
	}
	//print_cmdline(*cmd_line);
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
		if (loop_body(&line, &tokens, &cmd_line, &g_env))
			continue ;
		//print_list(tokens);
		free_tokens(tokens);
		//free_cmd(cmd_line);
		free(line);
	}
}

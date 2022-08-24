/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/24 11:54:28 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**get_paths(void)
{
	char	**paths;
	char	**ret;
	int		i;

	ret = 0;
	char	*tmp = getenv("PATH");
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
			ret[i] = ft_strjoin(ft_strdup(paths[i]), ft_strdup("/"));
			i++;
		}
		i = 0;
		while(paths[i])
			free(paths[i++]);
		free(paths);
		ret[i] = NULL;
	}
	return (ret);
}

void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

int	loop_body(char **line, t_token_list **tokens,
		t_cmd_list **cmd_line, t_env **g_env)
{
	int	status;

	(void) g_env;
	(void) cmd_line;
	status = 0;
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = tokenizer(*line);
	if (!check_syntax(*tokens))
	{
		is_heredoc(*tokens, status);
		expand(*tokens, g_env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		run_command(*cmd_line, *g_env);
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
	if (ac != 1)
		return (1);
	while (1)
	{
		setup_term();
		if (loop_body(&line, &tokens, &cmd_line, &g_env))
			continue ;
		free_tokens(tokens);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/28 14:51:50 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	loop_body(char **line, t_token_list **tokens,
		t_cmd_list **cmd_line, t_env **g_env)
{
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = tokenizer(*line);
	if (is_heredoc(*tokens, *g_env))
		return (0);
	if (!check_syntax(*tokens))
	{
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

	rl_catch_signals = 0;
	cmd_line = NULL;
	g_env = get_env(env);
	(void) av;
	if (ac != 1)
		return (1);
	while (1)
	{
		if (loop_body(&line, &tokens, &cmd_line, &g_env))
			continue ;
		free_tokens(tokens);
		free(line);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:43 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/19 18:35:21 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static char	*tokenizer_help(t_token_list *tokens, char *line)
{
	line = is_word(tokens, line, " \n\t\'\"<|>$;");
	if (*line == ';')
	{
		line++;
		if (*line == ';')
		{
			add_back(tokens, ft_strndup("syntax error near unexpected token \
				`;;'", 40), ERROR);
			line++;
		}
		else
			add_back(tokens, ft_strndup(";", 2), WORD);
	}
	return (line);
}

t_token_list	*tokenizer(char *line)
{
	t_token_list	*tokens;

	tokens = NULL;
	tokens = init_token_list(tokens);
	while (*line && *line != '\n')
	{
		if (ft_strchr(" \t\v\f\r", *line))
			line = is_wspace(tokens, line);
		else if (ft_strchr("<|>", *line))
			line = is_redpip(tokens, line);
		else if (ft_strchr("$~", *line))
			line = is_sign(tokens, line);
		else if (*line == '\'')
			line = is_squout(tokens, line);
		else if (*line == '\"')
			line = is_dquout(tokens, line + 1);
		else
			line = tokenizer_help(tokens, line);
	}
	return (tokens);
}
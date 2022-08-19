/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:18 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/19 15:51:39 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*is_word(t_token_list *tokens, char *line, char *stop)
{
	int	len;

	len = 0;
	while (!strchr(stop, line[len]))
		len++;
	if (len)
		add_back(tokens, ft_strndup(line, len + 1), WORD);
	return (line + len);
}

char	*is_squout(t_token_list *tokens, char *line)
{
	if (!ft_strchr(line + 1, '\''))
	{
		add_back(tokens, ft_strndup("error unclosed single quout",
				ft_strlen("error unclosed single quout") + 1), ERROR);
		return (line + 1);
	}
	if (*(line) == '\'')
		add_back(tokens, ft_strdup(""), WORD);
	line = is_word(tokens, line + 1, "\'");
	return (line + 1);
}

char	*is_dquout(t_token_list *tokens, char *line)
{
	if (!ft_strchr(line, '\"'))
	{
		add_back(tokens, ft_strndup("error unclosed double quout",
				ft_strlen("error unclosed double quout") + 1), ERROR);
		return (line + 1);
	}
	if (*(line) == '\"')
		add_back(tokens, ft_strdup(""), WORD);
	line = is_word(tokens, line, "$~\"");
	if (*line == '\"')
		line ++;
	else if (*line == '$' || *line == '~')
	{
		line = is_sign(tokens, line);
		if (*line == '\"')
			line++;
		else
			line = is_dquout(tokens, line);
	}
	return (line);
}

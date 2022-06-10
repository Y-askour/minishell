/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:21 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/10 18:17:38 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*ft_strndup(char *str, int n)
{
	char	*ret;

	ret = (char *)malloc(n);
	if (!ret)
		return (NULL);
	ft_strlcpy(ret, str, n);
	return (ret);
}

char *is_wspace(t_token_list *tokens, char *line)
{
    int len;

    len = 0;
    while(ft_strchr(" \t\f\r\v", line[len]))
        len++;
    add_back(tokens, " ", WHSPACE);
    return (line + len);
}

char *is_redpip(t_token_list *tokens, char *line)
{
    if (*line == '>')
    {
        if (*(line + 1) == '>')
        {
            add_back(tokens, ">>", APPEND);
            return (line + 2);
        }
        add_back(tokens, ">", REDOUT);
        return (line + 1);
    }
    else if (*line == '<')
    {
        if (*(line + 1) == '<')
        {
            add_back(tokens, "<<", HEREDOC);
            return (line + 2);
        }
        add_back(tokens, "<", REDOUT);
        return (line + 1);
    }
    else
        add_back(tokens, "|", PIPE);
    return (line + 1);
}

static char *after_dollar(t_token_list *tokens, char *line)
{
    int len;

    len = 0;
    /* i used in case we have to add other characters 
    if not replace it with line[line] == '_'*/
    while(ft_isalnum(line[len]) && !strchr("_", line[len]))
        len++;
    add_back(tokens, ft_strndup(line, len + 1), WORD);
    return(line + len);
}

char *is_sign(t_token_list *tokens, char *line)
{
    if (*line == '~')
    {
        add_back(tokens, "~", TILDE);
        line++;
    }
    else if (*line == '$')
    {
        add_back(tokens, "$", DOLLAR);
        line = after_dollar(tokens, line + 1);
    }
    return (line);
}
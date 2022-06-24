/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:43 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/20 20:00:05 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    tokenizer(t_token_list *tokens, char *line)
{
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
            line  = is_dquout(tokens, line + 1);
        else
        {
            line = is_word(tokens, line, " \n\t\'\"<|>$;\\");
            if (*line == ';' || *line == '\\')
            {
                if (*line == ';')
                    add_back(tokens, ft_strjoin("minishell: syntax error near unexpected token", " ';'"), ERROR);
                else
                    add_back(tokens, ft_strjoin("minishell: syntax error near unexpected token", " '\\'"), ERROR);
                line++;    
            }
        }
        /*check if there is ; or \
        if (*line  == ';' || *line == '\')
            add_back(error)
            return(NULL);*/
    }
 }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:43 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 17:56:25 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    tokenizer(t_token_list *tokens, char *line)
{
    // if (*line == '\"')
    //     line  = is_dquout(tokens, line + 1);
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
        {
            line  = is_dquout(tokens, line + 1);
           // printf("outside line:%s\n", line);
            //print_list(tokens);
            //exit (0);
        }
        else
            line = is_word(tokens, line, " \n\t\'\"<|>$");
    }
 }
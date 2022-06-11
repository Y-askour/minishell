/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_functions2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:18 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 17:55:22 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char *is_word(t_token_list *tokens, char *line, char *stop)
{
    int len;

    len = 0;
    while(!strchr(stop, line[len]))
        len++;
    if (len)
        add_back(tokens, ft_strndup(line, len + 1), WORD);
    return(line + len);
}

char *is_squout(t_token_list *tokens, char *line)
{
    if (!ft_strchr(line + 1, '\''))
    {
        add_back(tokens, ft_strndup("error unclosed single quout", 
                ft_strlen("error unclosed single quout")), ERROR);
        return(NULL);
    }
    line = is_word(tokens, line + 1, "\'");
    /*line + 1 because is_word retuns stop with line
    so it will return ' + the rest of the line*/
    return (line + 1);
}

char *is_dquout(t_token_list *tokens, char *line)
{
    if (!ft_strchr(line, '\"'))
    {
        add_back(tokens, ft_strndup("error unclosed double quout", 
                ft_strlen("error unclosed double quout") + 1), ERROR);
        //printf("EEEEEEEERRRRRRROOOOOOOORRRRRR\n");
        //printf("line sigf is:%s\n", line);
        //exit(0);
        return(NULL);
    }
    line = is_word(tokens, line, "$~\"");
    //printf("is_word returns:%s\n", line);
    if (*line == '"')
    {
       // printf("is_dooooobleeeee\n");
        //print_list(tokens);
        //printf("line is dooble:%s\n", line + 1);
        //exit(0);
        return (line + 1);
    }
    else if (*line == '$' || *line == '~')
    {
        line = is_sign(tokens, line);
        //printf("is_sign returns:%s\n", line);
        if (*line == '\"')
            return(line + 1);
        else
            line = is_dquout(tokens, line);
    }
    /*if is_sign returns " like if the line was like : "afdi$afdfj"*/
    return (line);
}
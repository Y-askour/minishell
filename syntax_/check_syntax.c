/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:25:30 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 23:46:27 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    check_already(t_token_elem *node)
{
    if (node->type == ERROR)
        error_handler(node->value);
}

void    check_pipe(t_token_elem *node)
{
    if (node->type == PIPE)
    {
        if(!node->next || node->next->type != WORD || !node->prev)
            error_handler("minishell: syntax error near unexpected token `|'");        
    }
}

void    check_red(t_token_elem *node)
{
    if (node->type == REDIN || node->type == REDOUT || node->type == APPEND || node->type == HEREDOC)
        {
            if (!node->next || node->next->type != WORD)
                error_handler("minishell: error no such file");
        }
}
void    check_syntax(t_token_list   *list)
{
    t_token_elem    *node;

    node = list->head;
    while (node)
    {
        check_already(node);
        check_pipe(node);
        check_red(node);
        node = node->next;
    }
}

//errors:
/*
not a word after redirection 
not a word after pip
pip at the begining of the line 
pip at the end of the line

*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:44:13 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 18:13:27 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    checker1(t_token_elem *node)
{
    if (node->type == -12)
        printf("%s\n", node->value);
}

void    check_syntax(t_token_list   *list)
{
    t_token_elem    *node;

    node = list->head;

    while (node)
    {
        checker1(node);
        node = node->next;
    }
}

t_token_list   lexical_analyser(char *line)
{
    t_token_list    *tokens;
    tokens = NULL;
    tokens = init_token_list(tokens);
    tokenizer(tokens, line);
    check_syntax(tokens);
    print_list(tokens);
    return (*tokens);
}
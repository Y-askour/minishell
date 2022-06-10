/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:44:13 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/10 21:35:31 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_list   lexical_analyser(char *line)
{
    t_token_list    *tokens;
   // printf("%s\n", line);
    tokens = NULL;
    tokens = init_token_list(tokens);
    tokenizer(tokens, line);
    print_list(tokens);
    return (*tokens);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:44:13 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/12 14:08:27 by yaskour          ###   ########.fr       */


#include"minishell.h"

t_token_list   *lexical_analyser(char *line)
{
    t_token_list    *tokens;
    tokens = NULL;
    tokens = init_token_list(tokens);
    tokenizer(tokens, line);
    //print_list(tokens);
    return (tokens);
}

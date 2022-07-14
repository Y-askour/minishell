/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:13:04 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/27 16:13:07 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_list	*lexical_analyser(char *line)
{
	t_token_list	*tokens;

	tokens = NULL;
	tokens = init_token_list(tokens);
	tokenizer(tokens, line);
	return (tokens);
}

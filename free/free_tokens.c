/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:48:01 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/23 19:39:14 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	free_tokens(t_token_list *tokens)
{
	t_token_elem	*tmp;

	tmp = tokens->head;
	while (tmp)
	{
		if (tmp->type == WORD || tmp->type == ERROR || \
			tmp->type == AFDOLLAR || tmp->type == EXITS || \
			tmp->type == DOLLAR)
			free(tmp->value);
		free(tmp);
		tmp = tmp->next;
	}
	free(tokens);
}

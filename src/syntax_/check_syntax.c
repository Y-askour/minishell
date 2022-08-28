/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:25:30 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/28 11:11:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_already(t_token_elem *node)
{
	if (node->type == ERROR)
	{
		error_handler(node->value, 258);
		return (1);
	}
	return (0);
}

int	check_pipe(t_token_elem *node)
{
	if (node->type == PIPE)
	{
		if (node->prev && node->prev->type == WHSPACE)
		{
			if (!node->prev->prev)
			{
				error_handler("minishell: syntax error near unexpected \
					token `|'", 258);
				return (1);
			}
		}
		if (node->next->type == WHSPACE)
			node = node->next;
		if (!node->next || (node->next && node->next->type == PIPE))
		{
			error_handler("minishell: syntax error near unexpected token `|'", \
					258);
			return (1);
		}
	}
	return (0);
}

int	check_red(t_token_elem *node, t_token_list *list)
{
	if (node->type == REDIN || node->type == REDOUT
		|| node->type == APPEND || node->type == HEREDOC)
	{
		if (node->next && node->next->type == WHSPACE)
			del_node(node->next, list);
		if (!node->next || (node->next->type != WORD && \
			node->next->type != DOLLAR && node->next->type != TILDE))
		{
			error_handler("syntax error near unexpected token `newline'", 258);
			return (1);
		}
	}
	return (0);
}

int	check_syntax(t_token_list *list)
{
	t_token_elem	*node;

	if (list->head->type == PIPE || list->taile->type == PIPE)
	{
		error_handler("syntax error near unexpected token `newline'", 258);
		return (1);
	}
	node = list->head;
	while (node)
	{
		if (check_already(node))
			return (1);
		if (check_pipe(node))
			return (1);
		if (check_red(node, list))
			return (1);
		node = node->next;
	}
	return (0);
}

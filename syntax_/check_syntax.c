/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:25:30 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/30 21:39:14 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_already(t_token_elem *node)
{
	if (node->type == ERROR)
	{
		error_handler(node->value);
		return (1);
	}
	return (0);
}

int	check_pipe(t_token_elem *node)
{
	if (node->type == PIPE)
	{
		if (!node->next || !node->prev)
		{
			error_handler("minishell: syntax error near unexpected token `|'");
			return (1);
		}
		if (node->next->type == WHSPACE)
		{
			if (!node->next->next || (node->next->next->type != AFDOLLAR && node->next->next->type != WORD))
			{ 
				error_handler("minishell: syntax error \
					near unexpected token `|'");
				return (1);
			}
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
		if (!node->next || node->next->type != WORD)
		{
			error_handler("minishell: error no such file");
			return (1);
		}
	}
	return (0);
}

int	check_syntax(t_token_list *list)
{
	t_token_elem	*node;

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

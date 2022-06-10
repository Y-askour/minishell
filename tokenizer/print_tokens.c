/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:53 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/10 18:50:51 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static void	print_node(t_token_elem *node)
{
	static int	n;

	n = 1;
	printf("--------------------------------------------------------------------------\n");
	printf("node: %d", n);
	printf(" => value: %s", node->value);
	printf(" => type: %i\n", node->type);
	n++;
}

void	print_list(t_token_list *list)
{
	t_token_elem	*node;

	node = list->head;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
}
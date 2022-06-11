/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:53 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 13:13:47 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


static void	print_node(t_token_elem *node)
{
	printf("--------------------------------------------------------------------------\n");
	printf("node:");
	printf(", value: %s", node->value);
	printf(", type: %i\n", node->type);
	write(1, "\n", 1);
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
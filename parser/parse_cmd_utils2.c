/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/13 16:20:24 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/19 12:29:25 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	count_args(t_token_elem *node)
{
	int	i;

	i = 0;
	while (node && node->type != PIPE)
	{
		if (node->type == WHSPACE)
			node = node->next;
		if (node)
			i++;
		while (node && node->type != WHSPACE)
			node = node->next;
	}
	return (i);
}

void	cmd_back(t_cmd_list *list, char **args, t_red_list *red)
{
	t_cmd_elem	*new;

	new = new_cmd(args, red);
	if (!list->head)
		list->head = new;
	else
	{
		list->taile->next = new;
		new->prev = list->taile;
	}
	list->taile = new;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:49 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/28 16:45:57 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_elem	*new_token(char *val, int type)
{
	t_token_elem	*new;

	new = malloc(sizeof (t_token_elem));
	new->type = type;
	new->value = val;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_back(t_token_list *list, char *val, int type)
{
	t_token_elem	*new;

	new = new_token(val, type);
	if (!list->head)
		list->head = new;
	else
	{
		list->taile->next = new;
		new->prev = list->taile;
	}
	list->taile = new;
}

t_token_list	*init_token_list(t_token_list *list)
{
	list = malloc(sizeof(t_token_list));
	list->head = NULL;
	list->taile = NULL;
	if (!list)
		return (NULL);
	return (list);
}

void	del_node(t_token_elem *node, t_token_list *list)
{
	if (node == NULL)
		return ;
	if (list->head == node)
		list->head = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->type == WORD || node->type == AFDOLLAR)
		free(node->value);
	free(node);
}

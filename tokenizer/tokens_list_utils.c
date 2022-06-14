/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:45:49 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/14 17:58:56 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_elem    *new_token(char *val, int type)
{
    t_token_elem    *new;

    new = malloc(sizeof (t_token_elem));
    new->type = type;
    new->value = val;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    add_back(t_token_list *list, char *val, int type)
{
    t_token_elem    *new;
    
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

void    del_node(t_token_elem *node, t_token_list *list)
{
    /* base case */
    if (node == NULL)
        return;
        
    if (list->head == node)
        list->head = node->next;
    /* Change next only if node to be deleted is NOT the last node */
    if (node->next != NULL)
        node->next->prev = node->prev;
 
    /* Change prev only if node to be deleted is NOT the first node */
    if (node->prev != NULL)
        node->prev->next = node->next;
    /* Finally, free the memory occupied by del*/
    if (node->type == WORD)
        free(node->value);
    free(node);
}
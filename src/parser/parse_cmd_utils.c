/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 21:38:21 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/28 23:03:28 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_cmd_list	*init_cmd_list(t_cmd_list *list)
{
	list = malloc(sizeof(t_cmd_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->taile = NULL;
	return (list);
}

t_red_list	*init_red_list(t_red_list *list)
{
	list = malloc(sizeof(t_red_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	list->taile = NULL;
	return (list);
}

t_red_elem	*new_red(int type, char *filename)
{
	t_red_elem	*new;

	new = malloc (sizeof(t_red_elem));
	if (!new)
		return (NULL);
	new->file = filename;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd_elem	*new_cmd(char **args, t_red_list *red)
{
	t_cmd_elem	*new;

	new = malloc(sizeof (t_cmd_elem));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->args = args;
	new->redir = red;
	return (new);
}

void	red_back(t_red_list *list, char *file, int type)
{
	t_red_elem	*new;

	new = new_red(type, file);
	if (!list->head)
		list->head = new;
	else
	{
		list->taile->next = new;
		new->prev = list->taile;
	}
	list->taile = new;
}

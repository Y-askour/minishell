/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:17:31 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/15 11:47:16 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_cmd_list	*init_cmd_list(t_cmd_list *list)
{
	list = malloc(sizeof(t_cmd_list));
    list->head = NULL;
    list->taile = NULL;
	if (!list)
		return (NULL);
	return (list);
}

t_red_list	*init_red_list(t_red_list *list)
{
	list = malloc(sizeof(t_red_list));
    list->head = NULL;
    list->taile = NULL;
	if (!list)
		return (NULL);
	return (list);
}

t_red_elem  *new_red(int type, char *filename)
{
    t_red_elem *new;

    new = malloc (sizeof(t_red_elem));
    new->file = filename;
    new->type = type;
    new->next = NULL;
    new->prev = NULL;
}
t_cmd_elem  *new_cmd(char **args, t_red_list *red)
{
    t_cmd_elem  *new;

    new = malloc(sizeof (t_cmd_elem));
    new->next = NULL;
    new->prev = NULL;
    new->args = args;
    new->redir = red;
}

void    red_back(t_red_list *list, char *file, int type)
{
    t_red_elem    *new;
    
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

void    cmd_back(t_cmd_list *list, char **args, t_red_list *red)
{
    t_cmd_elem    *new;
    
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

t_cmd_list  *parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line)
{
    t_token_elem  *tmp;
    t_cmd_list  *cmd_line;
    t_red_list  *red;

    cmd_line = init_cmd_list(cmd_line);
    red = init_red_list(red);
    tmp = tokens->head;
    while (tmp)
    {
        while(tmp->type != PIPE)
        {
            
        }
        tmp = tmp->next;
    }
}
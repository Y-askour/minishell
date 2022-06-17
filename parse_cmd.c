/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:17:31 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/17 21:28:17 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_elem  *one_cmd(t_cmd_list *list, t_token_elem *tmp)
{
    t_red_list  *red;
    
    red = init_red_list(red);
    while (tmp->type != PIPE)
    {
        tmp = tmp->next;
    }
    return (tmp)
}

t_cmd_list  *parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line)
{
    t_token_elem  *tmp;
    t_cmd_list  *cmd_line;

    cmd_line = init_cmd_list(cmd_line);
    tmp = tokens->head;
    while (cmd)
        tmp = one_cmd(cmd_lne, tmp);
    return (cmd_line);
}
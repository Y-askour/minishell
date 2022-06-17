/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:17:31 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/17 22:49:48 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

t_token_elem  *one_cmd(t_cmd_list *list, t_token_elem *tmp, t_token_list *list)
{
    t_red_list  *red;
    char **args;
    
    red = init_red_list(red);
    while (tmp->type != PIPE)
    {
        if (tmp->type == REDIN || tmp->type == REDOUT 
            || tmp->type == APPEND || tmp->type == HEREDOC)
        {
            red_back(red, tmp->next->value, tmp->type);
            del_node(tmp, list);
            de_node(tmp->next, list);
            tmp = tmp->next->next;        
        }
        args = ft_strjoin(tmp->value);
        tmp = tmp->next;
    }
    cmd_back(list, args, red);
    return (tmp);
}

t_cmd_list  *parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line)
{
    t_token_elem  *tmp;
    t_cmd_list  *cmd_line;

    cmd_line = init_cmd_list(cmd_line);
    tmp = tokens->head;
    while (tmp)
        tmp = one_cmd(cmd_line, tmp, tokens);
    return (cmd_line);
}
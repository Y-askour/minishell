/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:19:59 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/20 17:30:08 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void    print_args(char **args)
{
    int i;
    
    i = 0;
    printf("agrs are:");
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
    }
}

void    print_red(t_red_list *redir)
{
    t_red_elem *red;
    red  = redir->head;
    printf("reds:");
    while (red)
    {
        printf("  redir value:%d", red->type);
        printf("  filename:%s", red->file);
        if (!red->next)
            break;
        red = red->next;
    }
}

void    print_cmdline(t_cmd_list *cmdline)
{
    t_cmd_elem  *cmd;

    cmd = cmdline->head;
    while (cmd)
    {
        printf("\n============================================\n");
        print_red(cmd->redir);
        printf("\n");
        print_args(cmd->args);
        printf("\n============================================\n");
        cmd = cmd->next;
    }
    printf("\n");
}
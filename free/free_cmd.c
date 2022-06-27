/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:46:48 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/27 15:47:05 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void free_args(char **args)
{
	int i;
	
	i = 0;
	while(args[i])
	{
		free(args[i]);
		i++;
	}
	free(args[i]);
	free(args);
}
void	free_red(t_red_list *redir)
{
	t_red_elem *red;

	red = redir->head;
	while (red)
	{
		free(red->file);
		free(red);
		red = red->next;
	}
	free(redir);
}

void	free_cmd(t_cmd_list *cmdline)
{
	t_cmd_elem *cmd;

	cmd = cmdline->head;
	while(cmd)
	{
		free_args(cmd->args);
		free_red(cmd->redir);
		free(cmd);
		cmd = cmd->next;
	}
	free(cmdline);
}
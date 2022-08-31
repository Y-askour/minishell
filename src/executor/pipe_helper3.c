/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helper3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 12:29:37 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/31 12:11:59 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_out_check(t_pipe *in_out, int *i)
{
	in_out->in = 0;
	*i = 0;
	in_out->check = 0;
}

void	init_var(t_pipe *in_out, t_exec *var, t_g_env	*g_env, char **paths)
{
	pipe(in_out->fd);
	var->g_env = g_env;
	var->paths = paths;
	var->in = in_out->in;
	var->out = in_out->fd[1];
	var->close_first = in_out->fd[0];
}

void	change_exitstatus(int n)
{
	if (n == 2)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
	}
	else if (n == 3)
	{
		g_exit_status = 131;
		write(1, "Quit: 3\n", 8);
	}
	else
		g_exit_status = WEXITSTATUS(n);
}

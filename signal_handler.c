/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:37:04 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/04 13:37:34 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_handler(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();//Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
	rl_redisplay();//Change what's displayed on the screen to reflect the current contents of rl_line_buffer
}

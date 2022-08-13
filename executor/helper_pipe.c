/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:28:08 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/02 16:28:38 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_spaces_helper1(t_cmd_elem *head, int *i, int *n_of_arg)
{
	while (head->args[*i])
	{
		if (ft_strncmp(head->args[*i], " ", 1))
			*n_of_arg += 1;
		*i += 1;
	}
}

void	helper(char ***commands, t_cmd_elem **head, int *s, int j)
{
	commands[*s][j] = NULL;
	*head = (*head)->next;
	*s += 1;
}

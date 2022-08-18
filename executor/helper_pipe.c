/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:28:08 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/18 15:13:54 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

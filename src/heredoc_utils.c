/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:06:29 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/30 14:43:07 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	join_delimiter(t_token_elem *node, t_token_list *list)
{
	while (node->next && node->next->type != \
			PIPE && node->next->type != WHSPACE && \
			node->next->type != HEREDOC)
	{
		node->value = ft_strjoin(node->value, ft_strdup(node->next->value));
		del_node(node->next, list);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:17:31 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/13 15:05:32 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	count_args(t_token_elem *node)
{
	int	i;

	i = 0;
	while (node && node->type != PIPE)
	{
		if (node->type == WHSPACE)
		{
			i++;
			node = node->next;
		}
		if (node)
			i++;
		while (node && node->type != WHSPACE)
			node = node->next;
	}
	return (i);
}

void	del_red(t_cmd_list *cmd_line, t_token_elem *tmp, t_token_list *list)
{
	t_red_list	*red;

	red = NULL;
	red = init_red_list(red);
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		if (tmp->type == REDIN || tmp->type == REDOUT \
				|| tmp->type == APPEND || tmp->type == HEREDOC)
		{
			red_back(red, ft_strndup(tmp->next->value, \
						(int)ft_strlen(tmp->next->value) + 1), tmp->type);
			del_node(tmp->next, list);
			del_node(tmp, list);
		}
		tmp = tmp->next;
	}
	cmd_back(cmd_line, NULL, red);
	if (tmp && tmp->type == PIPE)
		del_red(cmd_line, tmp->next, list);
}

void	parse_args(t_cmd_elem *cmd_node, t_token_elem *node)
{
	int		i;
	char	**args;
	char	*str;

	i = count_args(node);
	args = malloc (sizeof(char *) * i + 1);
	i = 0;
	while (node)
	{
		if (node->type == WHSPACE)
		{
			args[i] = ft_strndup(" ", 2);
			i++;
			node = node->next;
		}
		if (!node || node->type == PIPE)
			break ;
		str = ft_strndup(node->value, (int)ft_strlen(node->value) + 1);
		while (node->next && node->next->type != WHSPACE && node->next->type != PIPE)
		{
			str = ft_strjoin(str, node->next->value); 
			node = node->next;
		}
		args[i] = str;
		i++;
		node = node->next;
	}
	args[i] = NULL;
	cmd_node->args = args;
	if (node && node->type == PIPE)
		parse_args(cmd_node->next, node->next);
}

t_cmd_list	*parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line)
{
	t_token_elem	*tmp;
	t_cmd_elem		*cmd_node;

	cmd_line = init_cmd_list(cmd_line);
	tmp = tokens->head;
	del_red(cmd_line, tmp, tokens);
	tmp = tokens->head;
	cmd_node = cmd_line->head;
	parse_args(cmd_node, tmp);
	return (cmd_line);
}

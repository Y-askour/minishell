/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/23 11:49:13 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_action(int exit_number, t_token_list *list,
		t_token_elem *node, int *fd)
{
	if (exit_number)
	{
		g_exit_status = exit_number;
		del_node(node->next, list);
		del_node(node, list);
		close(fd[1]);
		close(fd[0]);
	}
	else
	{
		close(fd[1]);
		node->type = REDIN;
		node->next->value = ft_itoa(fd[0]);
	}
}

void	heredoc_signal(int signal)
{
	(void) signal;
	exit(130);
}

void	input_heredoc(int *fd, t_token_elem *node)
{
	char	*input;

	signal(SIGINT, heredoc_signal);
	close(fd[0]);
	input = readline(">");
	if (!input)
		exit(0);
	while (ft_strncmp(input, node->next->value, \
			ft_strlen(node->next->value) + 1))
	{
		ft_putstr_fd(input, fd[1]);
		input = readline(">");
		if (!input)
			exit(0);
	}
	close(fd[1]);
	exit(0);
}

static void	join_delimiter(t_token_elem *node, t_token_list *list)
{
	while (node->next && node->next->type != \
			PIPE && node->next->type != WHSPACE)
	{
		node->value = ft_strjoin(node->value, ft_strdup(node->next->value));
		del_node(node->next, list);
	}
}

void	is_heredoc(t_token_list *list, int status)
{
	t_token_elem	*node;
	int				fd[2];
	int				pid;

	node = list->head;
	while (node)
	{
		if (node->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			join_delimiter(node->next, list);
			pipe(fd);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
				input_heredoc(fd, node);
			waitpid(pid, &status, 0);
			status = WEXITSTATUS(status);
			signal_action(status, list, node, fd);
			if (!node->next)
				break ;
		}
		node = node->next;
	}
}

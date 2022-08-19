/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/19 15:07:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_action(int pid, t_token_list *list, t_token_elem *node, int *fd)
{
	if (pid)
	{
		g_exit_status = pid;
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
		rl_on_new_line();
	}
	close(fd[1]);
	exit(0);
}

void	is_heredoc(t_token_list *list)
{
	t_token_elem	*node;
	int				fd[2];
	int				pid;
	int				status;

	node = list->head;
	while (node)
	{
		if (node->type == HEREDOC)
		{
			signal(SIGINT, SIG_IGN);
			pipe(fd);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
				input_heredoc(fd, node);
			waitpid(pid, &status, 0);
			pid = WEXITSTATUS(status);
			signal_action(pid, list, node, fd);
			if (!node->next)
				break ;
		}
		node = node->next;
	}
}

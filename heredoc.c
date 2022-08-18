/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/18 11:44:39 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	heredoc_signal(int signal)
{
	(void) signal;
	exit(1);
}

void	input_heredoc(int *fd, t_token_elem *node)
{
	char	*input;

	signal(SIGINT, heredoc_signal);
	close(fd[0]);
	input = readline(">");
	if (!input)
		exit(1);
	while (ft_strncmp(input, node->next->value, \
			ft_strlen(node->next->value) + 1))
	{
		ft_putstr_fd(input, fd[1]);
		input = readline(">");
		if (!input)
			exit(1);
		rl_on_new_line();
	}
	close(fd[1]);
	exit(1);
}

void	is_heredoc(t_token_list *list)
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
			pipe(fd);
			pid = fork();
			if (pid == -1)
				return ;
			if (pid == 0)
				input_heredoc(fd, node);
			else
				waitpid(pid, 0, 0);
			close(fd[1]);
			node->type = REDIN;
			node->next->value = ft_itoa(fd[0]);
		}
		node = node->next;
	}
}

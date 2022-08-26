/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/26 18:41:10 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_action(int exit_number, t_token_list *list, int *fd, t_env *env)
{	
	t_token_elem	*node;

	node = list->head;
	if (exit_number)
	{
		g_exit_status = exit_number;
		free_tokens(list);
		close(fd[1]);
		close(fd[0]);
		write(1, "\n", 1);
		main(1, NULL, lst_to_arr(env));
	}
	else
	{
		while (node->type != HEREDOC)
			node = node->next;
		close(fd[1]);
		free(node->next->value);
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
				max_len(input, node->next->value)))
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
			PIPE && node->next->type != WHSPACE && \
			node->next->type != HEREDOC)
	{
		node->value = ft_strjoin(node->value, ft_strdup(node->next->value));
		del_node(node->next, list);
	}
}

void	is_heredoc(t_token_list *list, int status, t_env *env)
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
			signal_action(status, list, fd, env);
			if (!node->next)
				break ;
		}
		node = node->next;
	}
}

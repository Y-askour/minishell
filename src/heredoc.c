/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/28 15:39:46 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_action(int exit_number, t_token_list *list, int *fd, t_env *env)
{	
	t_token_elem	*node;

	node = list->head;
	if (exit_number)
	{
		g_exit_status = 1;
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

	rl_catch_signals = 1;
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

int	is_heredoc2(t_token_elem *node, t_token_list *list, int *fd, t_env *env)
{
	int	status;
	int	pid;

	if (node->type == HEREDOC)
	{
		signal(SIGINT, SIG_IGN);
		if (heredoc_error(node, list))
			return (1);
		join_delimiter(node->next, list);
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			input_heredoc(fd, node);
		waitpid(pid, &status, 0);
		signal_action(status, list, fd, env);
	}
	return (0);
}

int	is_heredoc(t_token_list *list, t_env *env)
{
	t_token_elem	*node;
	int				fd[2];

	node = list->head;
	while (node)
	{
		if (is_heredoc2(node, list, fd, env))
			return (1);
		node = node->next;
	}
	return (0);
}

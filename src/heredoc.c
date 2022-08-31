/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 11:43:56 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/31 11:57:45 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	signal_action(t_norm var, t_token_list *list, int *fd, t_env *env)
{	
	if (var.heredoc)
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
		close(fd[1]);
		free(var.node->next->value);
		var.node->next->value = ft_itoa(fd[0]);
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
	int		status;
	int		pid;
	t_norm	var;

	if (node->type == HEREDOC)
	{
		signal(SIGINT, SIG_IGN);
		join_delimiter(node->next, list);
		pipe(fd);
		pid = fork();
		if (pid == -1)
			return (1);
		if (pid == 0)
			input_heredoc(fd, node);
		waitpid(pid, &status, 0);
		var.heredoc = status;
		var.node = node;
		signal_action(var, list, fd, env);
	}
	return (0);
}

int	is_heredoc(t_token_list *list, t_g_env *env)
{
	t_token_elem	*node;
	int				fd[2];
	t_env					*head;

	node = list->head;
	head = env->head;
	while (node)
	{
		if (check_syntax(list, node))
			return (1);
		if (is_heredoc2(node, list, fd, head))
			return (1);
		node = node->next;
	}
	return (0);
}

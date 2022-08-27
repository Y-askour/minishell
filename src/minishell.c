/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/08/27 15:18:24 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// void    print_args(char **args)
// {
//     int i;  
//     i = 0;
//     printf("agrs are:");
//     while (args[i])
//     {
//         printf("%s", args[i]);
//         i++;
//     }
//     printf("\n");
// }


// void    print_red(t_red_list *redir)
// {
//     t_red_elem  *red;

//     red  = redir->head;
//     printf("reds:");
//     while (red)
//     {
//         printf("  redir value:%d", red->type);
//         printf("  filename:%s", red->file);
//         if (!red->next)
//             break;
//         red = red->next;
//     }
// }

// void    print_cmdline(t_cmd_list *cmdline)
// {
//     t_cmd_elem  *cmd;

//     cmd = cmdline->head;
//     while (cmd)
//     {
//         printf("\n============================================\n");
//         print_red(cmd->redir);
//         printf("\n");
//         print_args(cmd->args);
//         printf("============================================\n");
//         cmd = cmd->next;
//     }
//     printf("\n");
// }
// static void	print_node(t_token_elem *node)
// {
// 	printf("--------------------------------------------------------------------------\n");
// 	printf("node:");
// 	printf("%s", node->value);
// 	printf(", type: %i\n", node->type);
// 	write(1, "\n", 1);
// }

// void	print_list(t_token_list *list)
// {
// 	t_token_elem	*node;

// 	node = list->head;
// 	while (node)
// 	{
// 		print_node(node);
// 		node = node->next;
// 	}
// 	printf("\n");
// }
void	setup_term(void)
{
	struct termios	t;

	tcgetattr(0, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

int	loop_body(char **line, t_token_list **tokens,
		t_cmd_list **cmd_line, t_env **g_env)
{
	int	status;

	status = 0;
	*line = display_prompt();
	if (!ft_strlen(*line))
		return (1);
	*tokens = tokenizer(*line);
	if (!check_syntax(*tokens))
	{
		is_heredoc(*tokens, status, *g_env);
		expand(*tokens, g_env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		//print_list(*tokens);
		//print_cmdline(*cmd_line);
		run_command(*cmd_line, *g_env);
		free_cmd(*cmd_line);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_token_list	*tokens;
	t_cmd_list		*cmd_line;
	t_env			*g_env;

	cmd_line = NULL;
	g_env = get_env(env);
	(void) av;
	if (ac != 1)
		return (1);
	while (1)
	{
		setup_term();
		if (loop_body(&line, &tokens, &cmd_line, &g_env))
			continue ;
		free_tokens(tokens);
		free(line);
	}
}

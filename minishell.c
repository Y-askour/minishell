/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:57:54 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	g_exit_status = 0;

char	**get_paths(char **env)
{
	char	**paths;
	char	**ret;
	int		i;

	(void)env;
	paths = ft_split(getenv("PATH"), ':');
	i = 0;
	while (paths[i])
		i++;
	ret = malloc(sizeof(char *) * i +1);
	i = 0;
	while (paths[i])
	{
		ret[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	shllvl(t_env *g_env)
{
	t_env	*temp;

	temp = g_env;
	while (temp)
	{
		if (!ft_strncmp(temp->name, "SHLVL", 5))
			break ;
		temp = temp->next;
	}
	temp->value = ft_itoa(ft_atoi(temp->value) + 1);
}

void	loop_body(char **line, t_token_list **tokens, char **env,
t_cmd_list **cmd_line, t_env **g_env)
{
	*line = display_prompt();
	*tokens = lexical_analyser(*line);
	if (!check_syntax(*tokens))
	{
		expand(*tokens, env);
		*cmd_line = parse_cmd(*tokens, *cmd_line);
		run_command(*cmd_line, env, *g_env);
	}
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
	shllvl(g_env);
	if (ac != 1 || !*env)
		return (1);
	while (1)
	{
		loop_body(&line, &tokens, env, &cmd_line, &g_env);
		free_tokens(tokens);
		free_cmd(cmd_line);
		free(line);
	}
}

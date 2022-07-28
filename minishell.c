/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:35:32 by aboudoun          #+#    #+#             */
/*   Updated: 2022/07/28 15:19:29 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	g_exit_status = 0;

char	**get_paths(char **env)
{
	t_env	*shell_env;
	t_env	*ptr;
	char	**paths;
	char	**ret;
	int		i;

	ptr = get_env(env);
	shell_env = ptr;
	while (shell_env)
	{
		if (!ft_strncmp(shell_env->name, "PATH", 4))
			break ;
		shell_env = shell_env->next;
	}
	paths = ft_split(shell_env->value, ':');
	while (ptr)
	{
		free(ptr->name);
		free(ptr->value);
		shell_env = ptr;
		ptr = ptr->next;
		free(shell_env);
	}
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
		line = display_prompt();
		tokens = lexical_analyser(line);
		if (!check_syntax(tokens))
		{
			expand(tokens, env);
			cmd_line = parse_cmd(tokens, cmd_line);
			run_command(cmd_line, env, g_env);
			//print_cmdline(cmd_line);
		}
		free_tokens(tokens);
		free_cmd(cmd_line);
		free(line);
	}
}

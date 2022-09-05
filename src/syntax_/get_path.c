/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 15:54:29 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/05 11:52:30 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*get_path(t_g_env *g_env)
{
	t_env	*env;

	env = g_env->head;
	while (env)
	{
		if (!ft_strncmp(env->name, "PATH", max_len(env->name, "PATH")))
			break ;
		env = env->next;
	}
	if (!env)
		return (NULL);
	return (env->value);
}

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	**get_paths(t_g_env *env)
{
	char	**paths;
	char	**ret;
	int		i;
	char	*tmp;

	ret = 0;
	tmp = get_path(env);
	if (tmp)
	{
		paths = ft_split(tmp, ':');
		i = 0;
		while (paths[i])
			i++;
		ret = malloc(sizeof(char *) * i +1);
		i = 0;
		while (paths[i])
		{
			ret[i] = ft_strjoin(ft_strdup(paths[i]), ft_strdup("/"));
			i++;
		}
		free_path(paths);
		ret[i] = NULL;
	}
	return (ret);
}

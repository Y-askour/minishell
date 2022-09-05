/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 11:06:14 by aboudoun          #+#    #+#             */
/*   Updated: 2022/09/05 11:10:57 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	**lst_to_arr(t_env *g_env)
{
	char	**env;
	t_env	*ptr;
	int		i;

	i = 0;
	ptr = g_env;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	env = malloc(sizeof(char *) * i + 1);
	ptr = g_env;
	i = 0;
	while (ptr)
	{
		env[i] = ft_strjoin(ft_strjoin(ft_strdup(ptr->name), \
					ft_strdup("=")), ft_strdup(ptr->value));
		i++;
		ptr = ptr->next;
	}
	env[i] = NULL;
	return (env);
}

int	search_env(char *name, char *value, t_g_env *g_env)
{
	t_env	*ptr;

	ptr = g_env->head;
	while (ptr)
	{
		if (!ft_strncmp(name, ptr->name, max_len(name, ptr->name)))
		{
			free(name);
			if (ptr->value)
				free(ptr->value);
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}

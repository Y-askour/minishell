/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:01:36 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/01 11:12:59 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	count_and_declare(int *i, char **command, t_env *env)
{
	while (command[*i])
		*i += 1;
	if (*i == 1)
		declare_export(env);
}

void	export_f(char **command, t_env *env)
{
	int		i;
	int		check;
	char	**split;

	i = 0;
	count_and_declare(&i, command, env);
	if (i >= 2)
	{
		i = 1;
		while (command[i])
		{
			check = 0;
			check_f(command[i], &check);
			if (check)
			{
				split = ft_split(command[i], '=');
				if (search_in_exp(&env, split))
					return ;
				add_env_node(split, &env);
			}
			i++;
		}
	}
	return ;
}

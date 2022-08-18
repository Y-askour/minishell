/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/18 11:50:29 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(char **command, t_env *env)
{
	char	*path;

	path = malloc(sizeof(char) * 255);
	chdir(command[1]);
	while (env)
	{
		if (!strncmp(env->name, "PWD", 3))
		{
			getcwd(path, PATH_MAX);
			env->value = path;
			break ;
		}
		env = env->next;
	}
	g_exit_status = 0;
}

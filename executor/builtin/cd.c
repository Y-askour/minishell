/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:58:59 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/16 19:40:52 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
	exit_status = 0;
}

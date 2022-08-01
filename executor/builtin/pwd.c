/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:00:50 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/01 11:01:14 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(char **command, t_env *env)
{
	char	*pwd;

	(void)command;
	while (env)
	{
		if (!ft_strncmp(env->name, "PWD", 3))
			break ;
		env = env->next;
	}
	pwd = env->value;
	printf("%s\n", pwd);
}

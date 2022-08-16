/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:00:50 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/16 17:51:20 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd(char **command, t_env *env)
{
	(void) command;
	(void) env;
	char	*pwd;
	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd,PATH_MAX);
	printf("%s\n", pwd);
}

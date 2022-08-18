/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:00:50 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/16 20:50:39 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **command, t_env *env)
{
	(void) command;
	(void) env;
	char	*pwd;
	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd,PATH_MAX);
	printf("%s\n", pwd);
}

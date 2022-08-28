/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaskour <yaskour@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 18:19:17 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/28 15:10:54 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	cd_to_check(char **command)
{
	struct stat	finfo;

	lstat(command[1], &finfo);
	if (!S_ISDIR(finfo.st_mode))
	{
		error_handler("cd : path: is not directory", 126);
		return (1);
	}
	if (access(command[1], X_OK))
	{
		error_handler("cd : path: Permission denied", 126);
		return (1);
	}
	return (0);
}

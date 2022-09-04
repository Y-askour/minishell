/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:00:50 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/04 13:52:56 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{	
	char	*pwd;

	pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(pwd, PATH_MAX);
	printf("%s\n", pwd);
	free(pwd);
}

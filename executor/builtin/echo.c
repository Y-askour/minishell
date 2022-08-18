/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:13:42 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/18 11:50:29 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char **command)
{
	int i = 1;
	while(command[i])
		printf("%s",command[i++]);
	printf("\n");
	g_exit_status = 0;
}

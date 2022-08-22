/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:13:42 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/22 19:18:33 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_option(char **command)
{
	int i = 0;
	while(command[i])
	{
		printf("%s\n",command[i++]);
	}
	return (0);
}

void	echo(char **command)
{
	int i = 1;
	int check = 0;
	if (check_option(command))
		check = 1;
	while(command[i])
	{
		printf("%s",command[i++]);
		if (command[i])
			printf(" ");
	}
	if (!check)
		printf("\n");
	g_exit_status = 0;
}

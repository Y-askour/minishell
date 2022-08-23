/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:13:42 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/23 12:13:22 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_option(char *command,int *check)
{
	int i;

	i = 0;
	if (command[0] == '-')
			i++;
	while(command[i])
	{
		if (!(command[i] == 'n'))
			return (1);
		i++;
	}
	*check = 1;
	return (0);
}

void	echo(char **command)
{
	int i = 1;
	int check=0;
	while(command[i])
	{
		if (check_option(command[i],&check))
			break ;
		i++;
	}
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

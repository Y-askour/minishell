/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:13:42 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 14:48:30 by yaskour          ###   ########.fr       */
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
	*check = 0;
	return (0);
}

void	echo(char **command)
{
	int i = 1;
	int check=1;
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
	//printf("%d\n",check);
	if (check)
		printf("\n");
	else
	{
		if (command[1])
		{
			int len = ft_strlen(command[1]);
			if (len == 0)
				printf("\n");
		}
		return;
	}
	g_exit_status = 0;
}

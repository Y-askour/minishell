/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 19:13:42 by yaskour           #+#    #+#             */
/*   Updated: 2022/09/03 15:47:08 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option(char *command, int *check)
{
	int	i;

	i = 0;
	if (command[0] == '-' && command[1])
		i++;
	else
		return (1);
	while (command[i])
	{
		if (command[i] != 'n')
			return (1);
		i++;
	}
	*check = 0;
	return (0);
}

void	echo_helper(char **command, int check)
{
	int	len;

	if (check)
		printf("\n");
	else
	{
		if (command[1])
		{
			len = ft_strlen(command[1]);
			if (len == 0)
				printf("\n");
		}
		return ;
	}
}

void	echo(char **command)
{
	int	i;
	int	check;

	i = 1;
	check = 1;
	while (command[i])
	{
		if (check_option(command[i], &check))
			break ;
		i++;
	}
	while (command[i])
	{
		printf("%s", command[i++]);
		if (command[i])
			printf(" ");
	}
	echo_helper(command, check);
	g_exit_status = 0;
}

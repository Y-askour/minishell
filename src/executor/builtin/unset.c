/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:14 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/31 13:56:10 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_valid(char *command)
{
	int	i;

	i = 0;
	if (ft_isalpha(command[i]) || command[i] == '_')
	{
		i++;
		while (command[i])
		{
			if (!ft_isalnum(command[i]) && !(command[i] == '_'))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	delete_node(char *name, t_g_env *env)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	tmp = env->head;
	prev = env->head;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name,name,max_len(name,tmp->name)))
		{
			if (i == 0)
				env->head = env->head->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
		}
		if (i > 0)
			prev = prev->next;
		tmp = tmp->next;
		i++;
	}
}

void	unset(char **command, t_g_env *g_env)
{
	int	i;


	i = 0;
	while (command[i])
		i++;
	if (i >= 2)
	{
		i = 1;
		while (command[i])
		{
			if (option(command[1]))
			{
				error_handler("minishell : export : invalid option", 1);
				return ;
			}
			else if (unset_valid(command[i]))
				delete_node(command[i], g_env);
			else
				error_handler("minishell: unset: `=` \
					:not a valid indentifier", 1);
			i++;
		}
	}
}

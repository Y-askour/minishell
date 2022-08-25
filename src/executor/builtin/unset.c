/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:55:14 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 20:31:00 by aboudoun         ###   ########.fr       */
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

void	delete_node(char *name, t_env *env)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*to_free;
	int		i;

	tmp = env;
	prev = env;
	to_free = env;
	i = 0;
	while (tmp)
	{
		if (!ft_strncmp(name, tmp->name, max_len(name, tmp->name)))
		{
			free(tmp->name);
			free(tmp->value);
			prev->next = tmp->next;
			free(to_free);
			break ;
		}
		if (i >= 1)
			prev = prev->next;
		tmp = tmp->next;
		to_free = to_free->next;
		i++;
	}
}

void	unset(char **command, t_env *env)
{
	int	i;

	(void)env;
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
				delete_node(command[i], env);
			else
				error_handler("minishell: unset: `=` \
					:not a valid indentifier", 1);
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:03 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/26 18:49:44 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	declare_export(t_env *env)
{
	int		i;
	t_env	*tmp;

	i = 0;
	while (i < 256)
	{
		tmp = env;
		while (tmp)
		{
			if (i == tmp->name[0])
			{
				printf("declare -x %s", tmp->name);
				if (ft_strncmp(tmp->value, "", max_len(tmp->value, "")))
					printf("=\"%s\"", tmp->value);
				printf("\n");
			}
			tmp = tmp->next;
		}
		i++;
	}
}

void	count_and_declare(int *i, char **command, t_env *env)
{
	while (command[*i])
		*i += 1;
	if (*i == 1)
		declare_export(env);
}

int	option(char *str)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == '-' && str[i + 1])
		return (1);
	return (0);
}

int	valid_loop(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		else if (!ft_isalnum(str[i]) && !(str[i] == \
			'=') && !(str[i] == '_'))
		{
			if (str[i] == '+' && str[i + 1])
			{
				if (!(str[i + 1] == '='))
					return (0);
			}
			else
				return (0);
		}
		if (i == ((int)ft_strlen(str) - 1))
			return (1);
		i++;
	}
	return (1);
}

int	valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
		return (valid_loop(str));
	return (0);
}

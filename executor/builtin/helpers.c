/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 11:05:03 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/24 20:30:52 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	declare_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

int max_len(char *str,char *str1)
{
	int len1;
	int len2;

	len1 = ft_strlen(str);
	len2 = ft_strlen(str1);
	if (len1 > len2)
		return (len1);
	return (len2);
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

int	valid(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
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
	return (0);
}

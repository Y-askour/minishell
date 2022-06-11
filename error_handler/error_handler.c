/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:25:36 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/11 23:48:19 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void error_handler(char *message)
{
    ft_putstr_fd(message, 2);
    write(1, "\n", 1);
    display_prompt();
}
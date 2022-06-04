/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:37:48 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/04 13:39:45 by aboudoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

// typedef struct s_list_
// {
//     struct s_list_ *list;
// }       t_list_;

// typedef struct s_command
// {
//     char **tab;
//     struct s_command *next;
//     struct s_command *prev;
//    // struct s_red;
// }       t_command;

// typedef struct s_red
// {
//     int type;
//     char *file;
//     struct s_red *next;
//     struct s_red *prev;
// }

void	signal_handler(int signal);

#endif

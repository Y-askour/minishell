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

# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_line
{
    struct s_line *head;
    struct s_line *taile;
}       t_line;

typedef struct s_cmd_ele
{
    char **args;
    struct s_cmd_ele *next;
    struct s_cmd_ele *prev;
    struct s_red *redir;
}       t_cmd_ele;

typedef struct s_red
{
    int type;
    char *file;
    struct s_red *next;
    struct s_red *prev;
}   t_red;

void	signal_handler(int signal);

#endif

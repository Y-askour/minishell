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

/******TOKENS*********/


typedef struct s_line
{
    struct s_line *head;
    struct s_line *taile;
}       t_line;

typedef struct s_cmd_elem
{
    char **args;
    struct s_cmd_elem *next;
    struct s_cmd_elem *prev;
    struct s_red_list *redir;
}       t_cmd_elem;

typedef struct s_red_elem
{
    int type;
    char *file;
    struct s_red_elem *next;
    struct s_red_elem *prev;
}       t_red_elem;

typedef struct s_cmd_list
{
    struct s_cmd_elem *head;
    struct s_cmd_elem *taile;
}       t_cmd_list;

typedef struct s_red_list
{
    struct s_red_elem *head;
    struct s_red_elem *taile;
}       t_red_list;

typedef struct s_token_list
{
    struct s_token_list *head;
    struct s_token_list *taile;
}       t_token_list;

typedef struct s_token_elem
{
    char *value;
    int type;
    struct s_token *next;
    struct s_token *prev;
}       t_token_elem;


void	signal_handler(int signal);

#endif

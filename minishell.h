# ifndef MINISHELL_H
# define MINISHELL_H

#include"libft/libft.h"
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include <readline/readline.h>
#include <readline/history.h>

// typedef struct s_list
// {
//     /* data */
// }   t_list;

void    signal_handler(int signal);

# endif
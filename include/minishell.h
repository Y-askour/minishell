/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 13:37:48 by aboudoun          #+#    #+#             */
/*   Updated: 2022/06/16 18:25:34 by yaskour          ###   ########.fr       */


#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define  PATH_MAX  50

/******TOKENS*********/
# define WORD -1
# define S_QUOTE -2
# define D_QUOTE -3
# define PIPE -4
# define APPEND -5 // >>
# define HEREDOC -6 // <<
# define REDIN -7
# define REDOUT -8
# define WHSPACE -9
# define DOLLAR -10
# define TILDE -11 // ~
# define ERROR -12


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


typedef struct s_token_elem
{
	char *value;
	int type;
	struct s_token_elem *next;
	struct s_token_elem *prev;
}       t_token_elem;

typedef struct s_cmd_list
{
	struct s_cmd_elem *head;
	struct s_cmd_elem *taile;
}       t_cmd_list;

typedef struct s_token_list
{
	struct s_token_elem *head;
	struct s_token_elem *taile;
}       t_token_list;

typedef struct s_red_list
{
	struct s_red_elem *head;
	struct s_red_elem *taile;
}       t_red_list;


typedef struct env t_env;
struct env
{
	char *name;
	char *value;
	t_env *next;
};


/** main functions **/
void	signal_handler(int signal);
char	*display_prompt();
int    check_syntax(t_token_list   *list);
void	error_handler(char *message);
t_token_list   *lexical_analyser(char *line);
t_cmd_list  *parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line);

/**** token_list functions ***/
void	print_list(t_token_list *list);
void	add_back(t_token_list *list, char *val, int type);
t_token_list	*init_token_list(t_token_list *list);
void    del_node(t_token_elem *node, t_token_list *list);
void	expand(t_token_list *list, char **env);
/******TOKENIZER FUNCTIONS*******/
void	tokenizer(t_token_list *tokens, char *line);
char	*is_word(t_token_list *tokens, char *line, char *stop);
char	*ft_strndup(char *str, int n);
char	*is_wspace(t_token_list *tokens, char *line);
char	*is_redpip(t_token_list *tokens, char *line);
char	*is_sign(t_token_list *tokens, char *line);
char	*is_squout(t_token_list *tokens, char *line);
char	*is_dquout(t_token_list *tokens, char *line);


// execution functions 


t_env *get_env(char **env);

#endif

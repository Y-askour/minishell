/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboudoun <aboudoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 15:57:31 by yaskour           #+#    #+#             */
/*   Updated: 2022/08/26 19:30:16 by yaskour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include "../libft/libft.h"
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <termios.h>
# define  PATH_MAX  50

/******TOKENS*********/
# define WORD -1
# define PIPE -4
# define APPEND -5 // >>
# define HEREDOC -6 // <<
# define REDIN -7
# define REDOUT -8
# define WHSPACE -9
# define DOLLAR -10
# define TILDE -11 // ~
# define ERROR -12
# define AFDOLLAR -13
# define EXITS -14

typedef struct s_cmd_elem
{
	char				**args;
	struct s_cmd_elem	*next;
	struct s_cmd_elem	*prev;
	struct s_red_list	*redir;
}	t_cmd_elem;

typedef struct s_red_elem
{
	int					type;
	char				*file;
	struct s_red_elem	*next;
	struct s_red_elem	*prev;
}	t_red_elem;

typedef struct s_token_elem
{
	char				*value;
	int					type;
	struct s_token_elem	*next;
	struct s_token_elem	*prev;
}	t_token_elem;

typedef struct s_cmd_list
{
	t_cmd_elem	*head;
	t_cmd_elem	*taile;
}	t_cmd_list;

typedef struct s_token_list
{
	struct s_token_elem	*head;
	struct s_token_elem	*taile;
}	t_token_list;

typedef struct s_red_list
{
	struct s_red_elem	*head;
	struct s_red_elem	*taile;
}	t_red_list;

typedef struct s_env
{
	char			**env;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec_var
{
	t_env			*g_env;
	char			**paths;
	int				in;
	int				out;
	int				close_first;
}	t_exec;

typedef struct s_pipe
{
	int				in;
	int				fd[2];
	int				check;
}	t_pipe;

typedef struct s_norm_var
{
	pid_t		pid;
	t_exec		var;
	t_pipe		in_out;
	int			status;
	t_cmd_elem	*ptr;

}	t_norm;

int				main(int ac, char **av, char **env);
/** main functions **/
char			*display_prompt(void);
int				check_syntax(t_token_list	*list);
int				error_handler(char *message, int status);
void			is_heredoc(t_token_list *list, int status, t_env *env);

t_cmd_list		*parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line);
/** cmd functions and utils**/
t_cmd_list		*init_cmd_list(t_cmd_list *list);
t_red_list		*init_red_list(t_red_list *list);
t_red_elem		*new_red(int type, char *filename);
t_cmd_elem		*new_cmd(char **args, t_red_list *red);
int				count_args(t_token_elem *node);
void			red_back(t_red_list *list, char *file, int type);
void			cmd_back(t_cmd_list *list, char **args, t_red_list *red);
t_token_elem	*one_cmd(t_cmd_list *cmd_line, \
		t_token_elem *tmp, t_token_list *list);
t_cmd_list		*parse_cmd(t_token_list *tokens, t_cmd_list *cmd_line);
/**** token_list functions ***/
void			add_back(t_token_list *list, char *val, int type);
t_token_list	*init_token_list(t_token_list *list);
void			del_node(t_token_elem *node, t_token_list *list);
void			expand(t_token_list *list, t_env **env);
/******TOKENIZER FUNCTIONS*******/
t_token_list	*tokenizer(char *line);
char			*is_word(t_token_list *tokens, char *line, char *stop);
char			*ft_strndup(char *str, int n);
char			*is_wspace(t_token_list *tokens, char *line);
char			*is_redpip(t_token_list *tokens, char *line);
char			*is_sign(t_token_list *tokens, char *line);
char			*is_squout(t_token_list *tokens, char *line);
char			*is_dquout(t_token_list *tokens, char *line);
/**free functions**/
void			free_cmd(t_cmd_list *cmdline);
void			free_tokens(t_token_list *tokens);

// execution functions 
char			***delete_spaces(t_cmd_elem *head, int n);
void			pipes_helper2(t_cmd_elem **head, int *fd, int *in);
int				pipes_helper1(int pid, int in, int *fd, int *check);
void			executer_helper(t_exec *var, int d, int n);
int				executer(int n, int i, t_cmd_elem *cmdline, t_exec *var);
char			**get_paths(t_env *env);
t_env			*get_env(char **env);

int				run_command(t_cmd_list *cmdline, t_env *g_env);
void			simple_cmd(t_cmd_elem *cmdline, t_env *g_env);
void			end_pipes(char **paths);

// builtins

int				builtins(char **command);
int				run_builtins(t_cmd_elem *cmdline, char **command, t_env *env);
void			cd(char **command, t_env *g_env);
void			pwd(char **command, t_env *g_env);
void			env_f(char **command, t_env *env);
void			exit_f(char **command);
int				redirections(t_cmd_elem *cmd_line, int in, int out);
int				export_f(char **command, t_env *env);
void			declare_export(t_env *env);
void			check_f(char *command, int *check);
int				search_in_exp(t_env **env, char **split);
void			add_env_node(char **split, t_env **env);
int				child(t_cmd_elem *cmdline, char **command,
					t_env *env, char **paths);
void			path_search_helper(char **command, int **check, char **env);
char			**simple_cmd_delete_spc(t_cmd_elem *cmdline);
int				check_dir(char *cmd, int check);
int				pipes_helper1(int pid, int in, int *fd, int *check);
void			pipes_helper2(t_cmd_elem **head, int *fd, int *in);
void			pipes_helper3(int in, int n);
char			***delete_spaces(t_cmd_elem *head, int n);
void			delete_spaces_helper1(t_cmd_elem *head, int *i, int *n_of_arg);
void			helper(char ***commands, t_cmd_elem **head, int *s, int j);
void			echo(char **command);
char			**lst_to_arr(t_env *g_env);
void			unset(char **command, t_env *env);
int				option(char *str);
int				max_len(char *str, char *str1);
int				valid(char *str);
void			count_and_declare(int *i, char **command, t_env *env);
void			change_exitstatus(int n);
int				g_exit_status;
void			init_out_check(t_pipe *in_out, int *i);
void			init_var(t_pipe *in_out, t_exec *var, \
t_env	*g_env, char **paths);
int				ft_is_number(char *str);
void			add_env_helper(t_env *g_env, char **split);
int				env_search(t_env *env, char *name, char *value);
#endif

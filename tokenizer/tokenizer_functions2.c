#include"minishell.h"


char *is_squout(t_token_list *tokens, char *line);
{
    if (!ft_strchr(line, "\'"))
        error_handler(1);
}
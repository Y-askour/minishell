#include"minishell.h"

void    tokenizer(t_token_list *tokens, char *line)
{
    while (*line && *line != '\n')
    {
        if (strchr(" \t\v\f\r", *line))
            line = is_wspace(tokens, line);
        else if (strchr("<|>", *line))
            line = is_redpip(tokens, line);
        else if (strchr("$~", *line))
            line = is_sign(tokens, line);
        else if (*line == '\'')
            line = is_squout(tokens, line);
        else if (*line == '"')
            line  = is_dqout(tokens, line);
        else
            is_word(tokens, line, " \t\'\"<|>");
    }
}
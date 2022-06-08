#include"minishell.h"

t_token_list   lexical_analyser(char *line)
{
    t_token_list    *tokens;

    tokenizer(tokens, line);
}
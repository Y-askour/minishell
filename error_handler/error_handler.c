#include"minishell.h"

void error_handler(char *message)
{
    ft_putstr_fd(message, 2);
    display_prompt();
}
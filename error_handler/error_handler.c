#include"minishell.h"

void error_handler(int error)
{
    if (error == 1)
        ft_putstr_fd("error unclosed single quouts\n", 2);
    else if (error == 2)
        ft_putstr_fd("error unclosed double quouts\n", 2);
    display_prompt();
}
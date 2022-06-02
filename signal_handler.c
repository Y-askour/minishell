#include"minishell.h"

void    signal_handler(int signal)
{
    if (signal == SIGINT)
        printf(" hi\n");
    return ;
}
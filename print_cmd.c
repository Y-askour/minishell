#include"minishell.h"

void    print_args(char **args)
{
    int i;
    
    i = 0;
    printf("agrs are:");
    while (args[i])
    {
        printf("%s", args[i]);
        i++;
    }
}

void    print_red(t_red_list *redir)
{
    t_red_elem *red;
    red  = redir->head;
    printf("reds:");
    while (red)
    {
        printf("  redir value:%d", red->type);
        printf("  filename:%s", red->file);
    }
}

void    print_cmdline(t_cmd_list *cmdline)
{
    t_cmd_elem  *cmd;

    cmd = cmdline->head;
    while (cmd)
    {
        printf("\n============================================\n");
        print_red(cmd->redir);
        printf("\n");
        print_args(cmd->args);
        cmd = cmd->next;
    }
    printf("\n");
}
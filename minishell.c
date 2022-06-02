#include"minishell.h"

int main(int ac, char **av)
{
    char *line;
    char *prompt;
    (void) ac;
    (void) av;

    prompt = "minishell$>";
    while (1)
    {
        signal(SIGINT, signal_handler); //ctrl + c
        signal(SIGQUIT, SIG_IGN); //ctrl + '\'
        signal(SIGTSTP, SIG_IGN); //ctrl + z
        line = readline(prompt);
        if (!line)
            exit(1);
        if (!ft_strncmp(line, "exit", 4))
        {
            printf("%s\n", line);
            exit(0);
        }
        printf("%s\n", line);
    }
}
// t_list  *head = NULL;
// t_list  *taile = NULL;
// head = malloc(sizeof(struct s_list));
// second = malloc(sizeof(struct s_list));
// taile = malloc(sizeof(struct s_list));
// if (ac > 2)
// {
//     head->argument = av[1];
//     head->next = second;
//     second->argument = av[2];
//     second->next = taile;
//     taile->argument = av[3];
//     taile->next = NULL;
// } 
// while(head)
// {
//     printf("%s\n", head->argument);
//     head = head->next;
// } 
#include"minishell.h"

void    checker1(t_token_elem *node)
{
    if (node->type == -12)
        printf("%s\n", node->value);
}
void    check_syntax(t_token_list   *list)
{
    t_token_elem    *node;

    node = list->head;

    while (node)
    {
        checker1(node);
        node = node->next;
    }
}
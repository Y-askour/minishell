#include"minishell.h"

t_token_elem    *new_token(char *val, int type)
{
    t_token_elem    *new;

    new = malloc(sizeof (t_token_elem));
    new->type = type;
    new->value = val;
    new->next = NULL;
    new->prev = NULL;
    return (new);
}

void    add_back(t_token_list *list, char *val, int type)
{
    t_token_elem    *new;
    
    new = new_token(val, type);
    if (!list->head)
        list->head = new;
    else
    {
        list->taile->next = new;
        new->prev = list->taile;
    }
    list->taile = new;
}

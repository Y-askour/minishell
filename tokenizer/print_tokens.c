#include"minishell.h"

void	print_node(t_token_elem *node)
{
	int	i;

	i = 0;
	printf("content: ");
	printf(", state: %s", node->value);
	printf(", token: %i\n", node->type);
}

void	print_list(t_token_list *list)
{
	t_token_elem	*node;

	node = list->head;
	while (node)
	{
		print_node(node);
		node = node->next;
	}
}
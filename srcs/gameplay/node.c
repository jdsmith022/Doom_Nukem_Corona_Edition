# include "../../includes/doom.h"

void	del_node(t_list **head, t_list *node)
{
	t_list *prev;

	prev = *head;
	if (prev->content == node->content)
	{
		*head = node->next;
		free(node);
		return ;
	}
	while (prev->next->content != node->content)
		prev = prev->next;
	prev->next = node->next;
	free(node);
}

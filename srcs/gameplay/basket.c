# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

void	init_basket()
{
	return ;
}

void	add_item_to_basket(t_list **head, uint8_t type)
{
	t_list *temp;
	t_item item;

	temp = *head;
	item.type = type;
	item.amount = 1;
	if (!temp){
		temp = ft_lstnew(&item, sizeof(t_item));
		*head = temp;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = ft_lstnew(&item, sizeof(t_item));
}

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

bool	remove_item_from_basket(t_list **head, uint8_t item)
{
	t_list *temp;

	temp = *head;
	if (!temp)
		return false;
	while (*((uint8_t *)temp->content) != item)
	{
		if (!temp->next)
			return false;
		temp = temp->next;
	}
	del_node(head, temp);
	return true;
}

void	print_basket(t_list **basket)
{
	t_list *temp;
	t_item item;

	temp = *basket;
	if (!temp)
		return ;
	while (temp){
		item = *(t_item *)temp->content;
		printf("type: %d amount: %d  ", item.type, item.amount);
		temp = temp->next;
	}
	printf("\n");
}

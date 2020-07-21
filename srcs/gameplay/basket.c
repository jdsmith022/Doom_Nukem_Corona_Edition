# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

uint8_t get_basket_len(t_list **head)
{
	uint8_t len;
	t_list *temp;

	temp = *head;
	if (!temp)
		return 0;
	len = 1;
	while (temp->next)
	{
		temp = temp->next;
		len++;
	}
	return len;
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
	while (!is_in_basket((t_item *)temp->content, type))
	{
		if (temp->next)
			temp = temp->next;
		else break ;
	}
	if (is_in_basket((t_item *)temp->content, type))
		change_amount((t_item *)temp->content, 1);
	else
		temp->next = ft_lstnew(&item, sizeof(t_item));
}

bool	remove_item_from_basket(t_list **head, uint8_t type)
{
	t_list *temp;
	t_item *item;

	temp = *head;
	if (!temp)
		return false;
	item = (t_item *)temp->content;
	while (item->type != type)
	{
		if (!temp->next)
			return false;
		temp = temp->next;
		item = (t_item *)temp->content;
	}
	change_amount(item, -1);
	if (item->amount == 0)
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
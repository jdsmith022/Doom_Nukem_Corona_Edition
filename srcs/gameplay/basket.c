# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

void	init_basket()
{
	return ;
}

void	add_item_to_basket(t_list **head, uint8_t item)
{
	t_list *temp;

	temp = *head;
	if (!temp){
		temp = ft_lstnew(&item, sizeof(uint8_t));
		*head = temp;
		return ;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = ft_lstnew(&item, sizeof(uint8_t));
}

void	remove_item_from_basket(t_list **head, uint8_t item)
{
	return ;
}

void	print_basket(t_list **basket)
{
	t_list *temp;

	temp = *basket;
	if (!temp)
		return ;
	while (temp){
		printf("%d\n", *((int *)temp->content));
		temp = temp->next;
	}
}

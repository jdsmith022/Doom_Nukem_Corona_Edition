# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

bool	is_in_basket(t_item *item, uint8_t type)
{
	if (item->type == type)
		return true;
	return false;
}

bool	search_basket(t_item *item, t_list **head)
{
	t_list *temp;

	temp = *head;
	if (!temp)
		return false;
	while (temp)
	{
		if (memcmp(temp->content, item, sizeof(t_item)) == 0)
			return true;
		if (temp->next)
			temp = temp->next;
		else break ;
	}
	return false;
}

bool	change_amount(t_item *item, int8_t amount)
{
	if (amount + item->amount == INT8_MAX)
		return false;
	else if (amount + item->amount == INT8_MIN)
		return false;
	item->amount += amount;
	return true;
}

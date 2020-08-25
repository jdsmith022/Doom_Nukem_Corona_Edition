#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

uint8_t	get_basket_len(t_list **head)
{
	uint8_t		len;
	t_list		*temp;

	temp = *head;
	if (!temp)
		return (0);
	len = 1;
	while (temp->next)
	{
		len++;
		temp = temp->next;
	}
	return (len);
}

bool			checkout(t_groceries *groceries)
{
	uint8_t		i;

	i = 0;
	if (groceries->shopping_list_len != get_basket_len(&groceries->basket))
		return (false);
	while (i < groceries->shopping_list_len)
	{
		if (!search_basket(&groceries->shopping_list[i], &groceries->basket))
			return (false);
		i++;
	}
	return (true);
}

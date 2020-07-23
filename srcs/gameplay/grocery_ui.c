#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

void	draw_basket_ui(t_doom *doom, t_groceries *groceries)
{
	t_list	*temp;
	t_item	*item;
	SDL_Rect position;

	temp = groceries->basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		draw_img(item->sprite, doom, item->position);
		temp = temp->next;
	}
	return ;
}

void	draw_shopping_ui(t_doom *doom, t_groceries *groceries)
{
	t_item		*item;
	SDL_Rect	position;
	uint16_t	i;

	i = 0;
	while (i < groceries->shopping_list_len)
	{
		draw_img(groceries->shopping_list[0].sprite, doom, groceries->shopping_list[0].position);
		i++;
	}
	return ;
}

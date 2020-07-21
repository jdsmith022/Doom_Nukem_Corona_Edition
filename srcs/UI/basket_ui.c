#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

void	set_position(t_coord *coord)
{
	coord->x += 50;
}

void	draw_basket_ui(t_doom *doom, t_groceries *groceries)
{
	t_list	*temp;
	t_item	*item;
	t_coord	coord;

	coord = (t_coord){.x = 50, .y = 50};
	temp = groceries->basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		draw_img(item->sprite, doom, coord);
		set_position(&coord);
		temp = temp->next;
	}
	return ;
}

void	draw_shopping_ui(t_doom *doom)
{
	// Loops through shopping list and draws sprites	
	return ;
}

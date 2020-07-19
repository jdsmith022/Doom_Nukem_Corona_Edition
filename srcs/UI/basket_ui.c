#include "../../includes/doom.h"

// void		put_textures(int x, int y, int index, t_doom *doom)
// void		draw_sprite(int x, int y, uint8_t index, t_doom *doom)

void	draw_basket_ui(t_doom *doom, t_groceries groceries)
{
	// Loops through basket and draws sprites with amount underneath
	t_list *temp;
	t_item *item;

	temp = groceries.basket;
	item = (t_item *)temp->content;
	draw_img(item->sprite, doom, 50, 50);
	return ;
}

void	draw_shopping_ui(t_doom *doom)
{
	// Loops through shopping list and draws sprites	
	return ;
}

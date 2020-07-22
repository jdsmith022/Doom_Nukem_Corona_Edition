#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

void	set_position(SDL_Rect *rect)
{
	rect->x += 50;
}

void	draw_basket_ui(t_doom *doom, t_groceries *groceries)
{
	t_list	*temp;
	t_item	*item;
	SDL_Rect position;

	position = (SDL_Rect){.x = 50, .y = 50, .w = 15, .h = 15};
	temp = groceries->basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		draw_img(item->sprite, doom, position);
		set_position(&position);
		temp = temp->next;
	}
	return ;
}

void	draw_shopping_ui(t_doom *doom, t_groceries *groceries)
{
	t_item		*item;
	SDL_Rect position;
	uint16_t	i;

	i = 0;
	position = (SDL_Rect){.x = WIDTH - 200, .y = 50,.w = 15, .h = 15};
	while (i < groceries->shopping_list_len)
	{
		draw_img(groceries->shopping_list[0].sprite, doom, position);
		set_position(&position);
		// draw_text_at(doom, position, "lol!");
		i++;
	}
	return ;
}

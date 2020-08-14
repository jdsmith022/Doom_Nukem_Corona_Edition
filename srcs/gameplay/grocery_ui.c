#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/font.h"

void			draw_item(t_doom *doom, t_item item)
{
	if (!item.sprite){
		printf("Sprite not found. Type: %d\n", item.type);
		return ;
	}
	draw_img(item.sprite, doom, item.position);
	draw_grocery_amount(doom, item.position, ft_itoa(item.amount));
}

void			draw_basket_ui(t_doom *doom, t_groceries *groceries)
{
	t_list		*temp;
	t_item		*item;
	SDL_Rect	position;

	temp = groceries->basket;
	while (temp)
	{
		item = (t_item *)temp->content;
		draw_item(doom, *item);
		temp = temp->next;
	}
	return ;
}

void			draw_shopping_ui(t_doom *doom, t_groceries *groceries)
{
	t_item		item;
	SDL_Rect	position;
	uint16_t	i;

	i = 0;
	while (i < groceries->shopping_list_len)
	{
		item = groceries->shopping_list[i];
		draw_item(doom, item);
		i++;
	}
	return ;
}

void			draw_grocery_amount(t_doom *doom, SDL_Rect rect, char *text)
{
	SDL_Color	font_color;
	TTF_Font	*font;
	SDL_Surface *font_surface;

	if (!font)
		doom_exit_failure(doom, "font error\n");
	font = doom->groceries->font;
	font_color = (SDL_Color){.r = 255, .g = 255, .b = 255};
	font_surface = TTF_RenderText_Solid(font, text, font_color);
	if (!font_surface)
		doom_exit_failure(doom, "font error\n");
	rect.y += 20;
	rect.x += 5;
	SDL_BlitSurface(font_surface, NULL, doom->surface, &rect);
}

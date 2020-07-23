#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/font.h"

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

void	draw_grocery_amount(t_doom *doom, SDL_Rect rect, char *text)
{
	SDL_Color	font_color;
	TTF_Font	*font;
	SDL_Surface *font_surface;

	TTF_Init();
	font = TTF_OpenFont("srcs/font/font_style/AmaticSC-Regular.ttf", 12);
	if (!font)
		doom_exit_failure(doom, "no font\n");
	font_color = (SDL_Color){.r = 255, .g = 255, .b = 255};
	font_surface = TTF_RenderText_Solid(font, text, font_color);
	if (!font_surface)
		doom_exit_failure(doom, "no surface\n");
	SDL_BlitSurface(font_surface, NULL, doom->surface, &rect);
	// SDL_BlitSurface(font_surface, NULL, doom->surface, &rect);
}

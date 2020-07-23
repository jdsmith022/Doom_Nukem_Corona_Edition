#include "../../includes/doom.h"

void	save_font_libraries(t_doom *doom)
{
	set_font_colors(doom);
	save_game_editor_font(doom, &doom->lib.font_lib.ge_font_len);
	save_hud_font(doom, &doom->lib.font_lib.hud_font_len);
	// save_basket_font(doom, &doom->lib.font_lib.basket_font_len);
}

void	draw_text_at(t_doom *doom, SDL_Rect rect, char *text)
{
	SDL_Color	font_color;
	TTF_Font	*font;
	SDL_Surface *font_surface;

	TTF_Init();
	font = TTF_OpenFont("srcs/UI/text/amatic/AmaticSC-Regular.ttf", 38);
	font_color = (SDL_Color){.r = 255, .g = 255, .b = 255};
	font_surface = TTF_RenderText_Solid(font, text, font_color);
	if (font_surface){
		SDL_BlitSurface(font_surface, NULL, doom->surface, &rect);
		free(font);
	}
}

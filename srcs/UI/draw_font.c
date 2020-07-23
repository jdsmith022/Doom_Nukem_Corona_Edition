/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/23 13:53:36 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		draw_font(t_doom *doom)
{
	Uint32	index;
	int		total_fonts;

	index = 0;
	total_fonts = doom->lib.len_font_lib;
	while (index < total_fonts)
	{
		// // SDL_BlitSurface(doom->lib.font_lib[index].font_surface, NULL,\
		// 	doom->surface, &doom->lib.font_lib[index].font_rect);
		// // SDL_Flip(doom->surface);
		index++;
	}
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

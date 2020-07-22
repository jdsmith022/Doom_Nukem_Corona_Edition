/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/22 20:38:14 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	draw_font(t_doom *doom, t_font *font_lib)
{
	Uint32	index;
	int		total_fonts;

	index = 0;
	total_fonts = font_lib->len;
	while (index < total_fonts)
	{
		SDL_BlitSurface(font_lib[index].font_surface, NULL,\
			doom->surface, &font_lib[index].font_rect);
		// // SDL_Flip(doom->surface);
		index++;
	}
}

void		select_font_lib(t_doom *doom)
{
	t_font	*font_lib;

	if (doom->game_editor == TRUE)
	{
		font_lib = doom->lib.font_lib->game_editor;
		draw_font(doom, font_lib);
	}
	// else if (doom->shopping == TRUE)
	// 	font_lib = doom->lib.font_lib->shopping_list;
	// else if (doom->basket == TRUE)
	// 	font_lib = doom->lib.font_lib->basket;
	// else if (doom->hud == TRUE)
	// 	font_lib = doom->lib.font_lib->hud;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/22 23:23:43 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	draw_font(t_doom *doom, t_font *font_lib, uint8_t len)
{
	Uint32	index;

	index = 0;
	while (index < len)
	{
		SDL_BlitSurface(font_lib[index].font_surface, NULL,\
			doom->surface, &font_lib[index].font_rect);
		// // SDL_Flip(doom->surface);
		index++;
	}
}

void		font_to_screen(t_doom *doom)
{
	t_font	*font_lib;
	uint8_t	len;

	if (doom->game_editor == TRUE)
	{
		font_lib = doom->lib.game_editor_font;
		len = doom->lib.ge_font_len;
		draw_font(doom, font_lib, len);
	}
	// else if (doom->shopping == TRUE)
	// 	font_lib = doom->lib.font_lib->shopping_list;
	// else if (doom->basket == TRUE)
	// 	font_lib = doom->lib.font_lib->basket;
	else if (doom->hud == TRUE)
	{
		font_lib = doom->lib.hud_font;
		len = doom->lib.hud_font_len;
		draw_font(doom, font_lib, len);
	}
}

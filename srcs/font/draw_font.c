/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/05 12:24:19 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	draw_font(t_doom *doom, t_font *font_lib, uint8_t len)
{
	Uint32	index;
	int		ret;

	index = 0;
	while (index < len)
	{
		ret = SDL_BlitSurface(font_lib[index].font_surface, NULL,\
			doom->surface, &font_lib[index].font_rect);
		if (ret == -1)
			doom_exit_failure(doom, FONT_ERR);
		index++;
	}
}

static void	font_to_screen_2(t_doom *doom)
{
	t_font	*font_lib;
	uint8_t	len;

	if (doom->shopping == TRUE)
	{
		font_lib = doom->lib.font_lib.shopping_font;
		len = doom->lib.font_lib.shopping_font_len;
		draw_font(doom, font_lib, len);
	}
	if (doom->basket == TRUE)
	{
		font_lib = doom->lib.font_lib.basket_font;
		len = doom->lib.font_lib.basket_font_len;
		draw_font(doom, font_lib, len);
	}
}

void		font_to_screen(t_doom *doom)
{
	t_font	*font_lib;
	uint8_t	len;

	if (doom->game_editor == TRUE)
	{
		font_lib = doom->lib.font_lib.game_editor_font;
		len = doom->lib.font_lib.ge_font_len;
		draw_font(doom, font_lib, len);
	}
	else if (doom->huds == TRUE)
	{
		font_lib = doom->lib.font_lib.hud_font;
		len = doom->lib.font_lib.hud_font_len;
		draw_font(doom, font_lib, len);
	}
	font_to_screen_2(doom);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/11 23:27:33 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void		draw_font(t_doom *doom, t_font *font_lib, uint8_t len)
{
	Uint32	index;

	index = 0;
	while (index < len)
	{
		SDL_BlitSurface(font_lib[index].font_surface, NULL,\
			doom->surface, &font_lib[index].font_rect);
		index++;
	}
}

static t_font	*font_to_screen_2(t_doom *doom,
					t_font *font_lib, uint8_t *len)
{
	if (doom->menu->pause == TRUE)
	{
		font_lib = doom->lib.font_lib.pause_font;
		*len = doom->lib.font_lib.pause_font_len;
	}
	else if (doom->menu->game_over == TRUE)
	{
		font_lib = doom->lib.font_lib.game_over_font;
		*len = doom->lib.font_lib.game_font_len;
	}
	else if (doom->menu->finished == TRUE)
	{
		font_lib = doom->lib.font_lib.finished_font;
		*len = doom->lib.font_lib.finished_font_len;
	}
	return (font_lib);
}

void			font_to_screen(t_doom *doom)
{
	t_font	*font_lib;
	uint8_t	len;

	if (doom->menu->menu == TRUE && doom->menu->settings == FALSE)
	{
		font_lib = doom->lib.font_lib.start_menu_font;
		len = doom->lib.font_lib.start_font_len;
	}
	else if (doom->menu->menu == TRUE && doom->menu->settings == TRUE)
	{
		font_lib = doom->lib.font_lib.setting_menu_font;
		len = doom->lib.font_lib.setting_font_len;
	}
	else if (doom->game_editor == TRUE)
	{
		font_lib = doom->lib.font_lib.game_editor_font;
		len = doom->lib.font_lib.ge_font_len;
	}
	else if (doom->hud_display == TRUE)
	{
		font_lib = doom->lib.font_lib.hud_font;
		len = doom->lib.font_lib.hud_font_len;
	}
	else
		font_lib = font_to_screen_2(doom, font_lib, &len);
	draw_font(doom, font_lib, len);
}

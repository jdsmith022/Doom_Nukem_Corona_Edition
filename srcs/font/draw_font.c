/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:10:03 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 23:52:31 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"

void			draw_font(t_doom *doom, t_font *font_lib, uint8_t len)
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
	if (doom->menu->state == game_paused)
	{
		font_lib = doom->lib.font_lib.pause_font;
		*len = doom->lib.font_lib.pause_font_len;
	}
	else if (doom->menu->state == game_over)
	{
		font_lib = doom->lib.font_lib.game_over_font;
		*len = 2;
	}
	else if (doom->menu->state == finished)
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

	len = 0;
	if (doom->menu->state == menu && doom->menu->settings == FALSE)
	{
		font_lib = doom->lib.font_lib.start_menu_font;
		len = doom->lib.font_lib.start_font_len;
	}
	else if (doom->menu->settings == TRUE)
	{
		font_lib = doom->lib.font_lib.setting_menu_font;
		len = doom->lib.font_lib.setting_font_len;
	}
	else if (doom->game.editor == TRUE)
	{
		font_lib = doom->lib.font_lib.game_editor_font;
		len = doom->lib.font_lib.ge_font_len;
	}
	else
		font_lib = font_to_screen_2(doom, font_lib, &len);
	if (len != 0)
		draw_font(doom, font_lib, len);
}

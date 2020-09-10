/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 15:14:21 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		set_draw_sidedef(t_doom *doom, Uint32 **pixels)
{
	t_sidedef 	sidedef;
	int			index;

	index = 0;
	while (index < doom->lib.len_sidedef)
	{
		sidedef = doom->lib.sidedef[index];
		draw_ed_sidedef(doom, pixels, &sidedef);
		index++;
	}
}

void			open_game_editor(t_doom *doom, double dt)
{
	Uint32				*pixels;

	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	init_game_design(doom);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->own_event.mouse_pointer = TRUE;
	while (doom->game.editor == TRUE)
	{
		doom->cast.distance = 1;
		pixels = doom->surface->pixels;
		draw_screen_colors(pixels, doom);
		draw_images(pixels, doom);
		highlight_curr_sector(doom);
		set_draw_sidedef(doom, &pixels);
		draw_ed_sprite(doom, &pixels);
		draw_font(doom, doom->lib.font_lib.game_editor_font,\
			doom->lib.font_lib.ge_font_len);
		set_to_window(doom);
		sdl_poll_events(doom, dt);
	}
	add_lists_to_libs(doom);
}

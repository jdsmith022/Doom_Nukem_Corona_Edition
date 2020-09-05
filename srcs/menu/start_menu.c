/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_menu.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:28 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/04 09:43:21 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/font.h"
#include "../../includes/hud.h"

static void	set_menu_game_variables(t_doom *doom)
{
	t_font font_lib;

	font_lib = doom->lib.font_lib.instruction_font[28];
	doom->lib.font_lib.bools.walking_info = TRUE;
	doom->lib.font_lib.bools.walking_text = TRUE;
	doom->lib.font_lib.bools.start_sector = TRUE;
	doom->lib.font_lib.bools.trolly = FALSE;
	doom->lib.font_lib.bools.checkout = TRUE;
	doom->lib.font_lib.bools.scissor_lift = FALSE;
	doom->lib.font_lib.bools.text = FALSE;
	doom->hud->hold_time /= doom->game.difficulty;
	doom->hud->curr_time /= doom->game.difficulty;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (doom->game.editor == FALSE)
	{
		SDL_BlitSurface(font_lib.font_surface, NULL, \
			doom->surface, &font_lib.font_rect);
		SDL_UpdateWindowSurface(doom->window);
	}
}

void		doom_start(t_doom *doom)
{
	init_menu(doom);
	init_audio(doom);
	doom->game.difficulty = 1;
	while (doom->menu->state != start_game)
	{
		mouse_settings(doom);
		if (doom->menu->settings == FALSE)
			print_background(doom, 0x00002E);
		else
		{
			print_background(doom, 0xF2F2F2);
			print_player_sprite(doom);
		}
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
	set_menu_game_variables(doom);
}

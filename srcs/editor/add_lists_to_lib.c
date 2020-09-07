/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_lists_to_lib.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 22:49:55 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

static void		set_gameplay_settings(t_doom *doom)
{
	doom->pos = doom->pos;
	doom->lib.sector = light_correction(\
		doom->lib.sector, doom->game_design.sc_len);
	doom->player.height = PLAYER_HEIGHT \
		+ doom->lib.sector[doom->i_sector].height_floor;
	doom->game.light = TRUE;
	doom->menu->state = start_game;
	doom->menu->start_timer = FALSE;
	doom->lib.sector[doom->i_sector].action = START_TIMER;
	doom->game.hud_display = TRUE;
	doom->lib.font_lib.bools.walking_info = TRUE;
	doom->lib.font_lib.bools.walking_text = TRUE;
	doom->lib.font_lib.bools.start_sector = TRUE;
	doom->lib.font_lib.bools.trolly = FALSE;
	doom->lib.font_lib.bools.checkout = TRUE;
	doom->lib.font_lib.bools.scissor_lift = FALSE;
	doom->lib.font_lib.bools.text = FALSE;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	doom->own_event.mouse_pointer = FALSE;
	clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	SDL_UpdateWindowSurface(doom->window);
}

static void		flush_sector_list_info(t_doom *doom)
{
	doom->game_design.ed_sector->light_level = doom->game_design.light_level;
	doom->game_design.ed_sector->height_floor = doom->game_design.floor_height;
	doom->game_design.ed_sector->height_ceiling = \
		doom->game_design.ceiling_height;
}

void			add_lists_to_libs(t_doom *doom)
{
	del_groceries(doom->groceries);
	flush_sector_list_info(doom);
	set_sector_lib(doom);
	set_sprite_lib(doom);
	set_sidedef_lib(doom);
	set_gameplay_settings(doom);
	init_groceries(doom);
	printf("start sector = %d\n", doom->i_sector);
}

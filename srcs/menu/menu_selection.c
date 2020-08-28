/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_selection.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:18:21 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:18:22 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"

static void		finished_menu(t_doom *doom)
{
	add_score_to_sdl_text(doom);
	while (doom->menu->state == finished)
		menu_print_loop(doom);
}

static void		game_over_menu(t_doom *doom)
{
	while (doom->menu->state == game_over)
		menu_print_loop(doom);
}

static void		pause_menu(t_doom *doom)
{
	struct timespec hold_time;
	struct timespec curr_time;

	clock_gettime(doom->game_time, &hold_time);
	while (doom->menu->state == game_paused)
	{
		Mix_PauseMusic();
		menu_print_loop(doom);
	}
	resume_music();
	clock_gettime(doom->game_time, &curr_time);
	doom->game_start_time.tv_sec = \
		doom->game_start_time.tv_sec + (curr_time.tv_sec - hold_time.tv_sec);
	doom->hud_display = TRUE;
	SDL_SetRelativeMouseMode(TRUE);
}

void			menus(t_doom *doom)
{
	if (doom->menu->state == game_over)
		game_over_menu(doom);
	if (doom->menu->state == game_paused)
		pause_menu(doom);
	if (doom->menu->state == finished)
		finished_menu(doom);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_selection.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:02 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 21:10:33 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"

static void		menu_settings(t_doom *doom)
{
	doom->game.hud_display = FALSE;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(doom->cursor);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

static void		get_missing_groceries(t_doom *doom, int *empty, int *list)
{
	char		*score;
	t_item		*info;
	size_t		index;

	index = 0;
	while (list[index])
	{
		list[index] = -1;
		index++;
	}
	info = doom->groceries->info.groceries_to_display;
	info->position.y = HEIGHT - 200;
	info->position.x = WIDTH / doom->groceries->shopping_list_len - 25;
	index = 0;
	while (index < doom->groceries->shopping_list_len)
	{
		info->position.x += 100;
		if (info[index].amount != 0)
			list[index] = index;
		if (info[index].amount == 0)
			*empty += 1;
		index++;
	}
}

static void		finished_menu(t_doom *doom)
{
	int	list[doom->groceries->shopping_list_len];
	int	empty;

	empty = -1;
	stop_sounds();
	play_sound(doom->audio->sounds[LVL_FINISH], -1);
	if (doom->groceries)
	{
		if (doom->groceries->info.won == FALSE && \
		doom->menu->state == finished)
			get_missing_groceries(doom, &empty, list);
	}
	add_score_to_sdl_text(doom, empty);
	menu_settings(doom);
	while (doom->menu->state == finished)
		menu_print_loop(doom, empty);
}

static void		pause_menu(t_doom *doom)
{
	struct timespec hold_time;
	struct timespec curr_time;

	clock_gettime(doom->game.play_time, &hold_time);
	menu_settings(doom);
	while (doom->menu->state == game_paused)
	{
		Mix_PauseMusic();
		menu_print_loop(doom, -1);
	}
	resume_music();
	clock_gettime(doom->game.play_time, &curr_time);
	doom->game.start_time.tv_sec = \
		doom->game.start_time.tv_sec + (curr_time.tv_sec - hold_time.tv_sec);
	doom->game.hud_display = TRUE;
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

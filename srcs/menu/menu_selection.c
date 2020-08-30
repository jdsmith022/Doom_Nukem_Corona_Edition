/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_selection.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:02 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/30 11:27:23 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"
#include "../../includes/hud.h"

static void		set_reason_and_statement(t_doom *doom, char **reason, char **statement)
{
	if (doom->hud->corona_level < 100)
	{
		*reason = "Oh bummer! You ran out of time!!";
		*statement = "Try again and keep safe!";
	}
	else
	{
		*reason = "You're corona level reached 100!";
		*statement = "Time to self-quarantine!";
	}
	
}

static void		set_reason_for_gameover(t_doom *doom)
{
	TTF_Font	*font;
	char		*reason;
	char		*statement;
	
	font = doom->lib.font_lib.font_30;
	set_reason_and_statement(doom, &reason, &statement);
	doom->lib.font_lib.game_over_font[2].str = reason;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[2], font);
	doom->lib.font_lib.game_over_font[3].str =  statement;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[3], font);
}

static void	game_over_menu(t_doom *doom)
{
	while (doom->menu->state == game_over)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		mouse_settings(doom);
		doom->hud_display = FALSE;
		print_background(doom, 0x00002E);
		set_reason_for_gameover(doom);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

static void		finished_menu(t_doom *doom)
{
	add_score_to_sdl_text(doom);
	while (doom->menu->state == finished)
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

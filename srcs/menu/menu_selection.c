/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu_selection.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:15:02 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 16:16:26 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"
#include "../../includes/hud.h"

static void		set_reason_for_gameover(t_doom *doom)
{
	TTF_Font	*font;
	
	printf("here\n");
	font = doom->lib.font_lib.font_30;
	doom->lib.font_lib.game_over_font[1].str = "Oh bummer! You ran out of time!!";
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[1], font);
	printf("1: %s\n", doom->lib.font_lib.game_over_font[1].str);
	doom->lib.font_lib.game_over_font[2].str =  "Try again and keep safe!";
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[2], font);
	printf("2: %s\n", doom->lib.font_lib.game_over_font[2].str);
	printf("end");
}

static void	game_over_menu(t_doom *doom)
{
	while (doom->menu->state == game_over)
	{
		doom->hud_display = FALSE;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		print_background(doom, 0x00002E);
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
	{
		printf("yo\n");
		if (doom->hud->corona_level < 100)
			set_reason_for_gameover(doom);
		game_over_menu(doom);
	}
	if (doom->menu->state == game_paused)
		pause_menu(doom);
	if (doom->menu->state == finished)
		finished_menu(doom);
}

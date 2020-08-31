/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over_menu.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:28:12 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 16:29:09 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"
#include "../../includes/hud.h"

static void		set_reason(t_doom *doom, char **reason, char **statement)
{
	if (doom->hud->corona_level >= 100)
	{
		*reason = "You're corona level reached 100!";
		*statement = "Time to self-quarantine!";
	}
	else
	{
		*reason = "Oh bummer! You ran out of time!!";
		*statement = "Try again and keep safe!";
	}
}

static void		set_reason_for_gameover(t_doom *doom)
{
	TTF_Font	*font;
	char		*reason;
	char		*statement;

	font = doom->lib.font_lib.font_30;
	set_reason(doom, &reason, &statement);
	doom->lib.font_lib.game_over_font[2].str = reason;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[2], font);
	doom->lib.font_lib.game_over_font[3].str = statement;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[3], font);
}

void			game_over_menu(t_doom *doom)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	stop_sounds();
	play_sound(doom->audio->sounds[GAMEOVER], -1);
	while (doom->menu->state == game_over)
	{
		doom->hud_display = FALSE;
		mouse_settings(doom);
		print_background(doom, 0x00002E);
		set_reason_for_gameover(doom);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:49 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 15:28:06 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void		set_reason_for_gameover(t_doom *doom)
{
	TTF_Font	*font;
	char		*reason;
	char		*status;
	
	printf("here\n");
	reason = "Oh bummer! You ran out of time!!";
	status = "Try again and keep safe!";
	font = doom->lib.font_lib.font_30;
	doom->lib.font_lib.game_over_font[1].str = reason;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[1], font);
	doom->lib.font_lib.game_over_font[2].str = status;
	single_font_to_sdl(doom, doom->lib.font_lib.game_over_font[2], font);
}

void	check_levels_and_time(t_doom *doom)
{
	while (doom->menu->state == game_over)
	{
		doom->hud_display = FALSE;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		if (doom->hud->corona_level < 100)
			set_reason_for_gameover(doom);
		print_background(doom, 0x00002E);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

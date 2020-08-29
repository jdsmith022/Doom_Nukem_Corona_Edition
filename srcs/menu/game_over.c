/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:49 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 17:40:55 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"

void	check_levels_and_time(t_doom *doom)
{
	while (doom->menu->state == game_over)
	{
		doom->hud_display = FALSE;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		SDL_SetCursor(doom->cursor);
		mouse_settings(doom);
		print_background(doom, 0x00002E);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:56:13 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/04 12:39:18 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	doom_gui(t_doom *doom)
{
	(void)doom;
}

void 	doom_sound(t_doom *doom)
{
	(void)doom;
}

void	game_loop(t_doom *doom)
{
	while (doom->esc == 0) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		doom_input(doom);
		doom_render(doom);
		sprite_render(doom); //is this the best place??
		doom_sound(doom);
		doom_gui(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, HEIGHT * WIDTH * 4);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:56:13 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/26 15:34:38 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	doom_gui(t_doom *doom)
{
	(void)doom;
}

void	doom_sound(t_doom *doom)
{
	(void)doom;
}

void	game_loop(t_doom *doom)
{
	while (doom->esc == 0) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		doom_input(doom);
		doom_render(doom);
		doom_sound(doom);
		doom_gui(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

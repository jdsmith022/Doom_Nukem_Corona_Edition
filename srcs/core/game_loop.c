/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:56:13 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/31 21:36:32 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
	struct timespec	t;
	long last_frame_time;
	float	dt;

	last_frame_time = 0;
	while (doom->is_running == TRUE) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		clock_gettime(CLOCK_MONOTONIC_RAW, &t);
		dt = t.tv_nsec - last_frame_time;
		dt /= 100000;
		last_frame_time = t.tv_nsec;
		printf("%f\n", dt);
		doom_update(doom, dt);
		doom_render(doom);
		doom_sound(doom);
		doom_gui(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
}

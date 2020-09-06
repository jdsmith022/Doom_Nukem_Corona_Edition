/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/05 21:11:05 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

void		set_to_window(t_doom *doom)
{
	SDL_UpdateWindowSurface(doom->window);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

double			get_timeframe(long *last_frame_time)
{
	struct timespec t;
	double			dt;

	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
	dt = t.tv_nsec - *last_frame_time;
	dt /= round(1.0e9);
	if (dt < 0)
		dt = 0;
	*last_frame_time = t.tv_nsec;
	return (dt);
}

void			game_loop(t_doom *doom)
{
	long			last_frame_time;
	double			dt;
	int 			i;

	last_frame_time = 0;
	i = 0;
	dt = get_timeframe(&last_frame_time);
	while (doom->game.is_running == TRUE)
	{
		// printf("check 1: %i\n", i);
		dt = get_timeframe(&last_frame_time);
		// printf("check 2: %i\n", i);
		doom_update(doom, dt);
		// printf("check 3: %i\n", i);
		timer(doom);
		// printf("check 4: %i\n", i);
		if (doom->game.editor == FALSE && doom->menu->state == start_game)
			doom_render(doom);
		// printf("check 5: %i\n", i);
		update_screen(doom);
		// printf("check 6: %i\n", i);
		set_to_window(doom);
		// printf("check 7: %i\n", i);
		i++;
	}
	doom_exit_success(doom);
}

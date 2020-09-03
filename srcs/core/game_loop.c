/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/03 16:13:15 by jesmith       ########   odam.nl         */
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

	last_frame_time = 0;
	dt = get_timeframe(&last_frame_time);
	while (doom->game.is_running == TRUE)
	{
		dt = get_timeframe(&last_frame_time);
		doom_update(doom, dt);
		// printf("test11: %d\n", doom->lib.sidedef[0].id);
		// printf("sd len: %d\n", doom->game_design.sd_len);
		timer(doom);
		doom_render(doom);
		// printf("test: %d\n", doom->lib.sector[doom->i_sector].id);
		// printf("test22: %d\n", doom->lib.sidedef[0].id);
		update_screen(doom);
		set_to_window(doom);
	}
	doom_exit_success(doom);
}

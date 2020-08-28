
#include "../../includes/doom.h"

static void		set_to_window(t_doom *doom)
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
	while (doom->is_running == TRUE)
	{
		timer(doom);
		dt = get_timeframe(&last_frame_time);
		// while (doom->game_state == updated)
		doom_update(doom, dt);
		doom_render(doom);
		update_hud_ui(doom);
		set_to_window(doom);
		// doom->game_state = updated;
	}
	doom_exit_success(doom);
}

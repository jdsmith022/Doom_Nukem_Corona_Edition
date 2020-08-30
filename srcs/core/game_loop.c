
#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

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
		printf("0");	
		timer(doom);
		printf("1");
		dt = get_timeframe(&last_frame_time);
		printf("2");
		doom_update(doom, dt);
		printf("3");
		if (doom->game_editor == FALSE && doom->menu->state == start_game)
			doom_render(doom);
		printf("4");
		update_screen(doom);
		printf("5");
		set_to_window(doom);
		printf("6");
	}
	printf("7");
	doom_exit_success(doom);
}

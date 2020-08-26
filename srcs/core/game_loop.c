
#include "../../includes/doom.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"

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
	dt = t.tv_sec - *last_frame_time;
	dt /= round(1000);
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
		printf("%f\n", dt);
		timer(doom);
		dt = get_timeframe(&last_frame_time);
		if (doom->game_editor == FALSE && doom->menu->game_over == FALSE)
		{
			sprite_reset(doom);
			doom_render(doom);
			audio(doom, &doom->own_event);
			groceries(doom);
		}
		else if (doom->game_editor == TRUE && doom->menu->game_over == FALSE)
			open_game_editor(doom);
		doom_update(doom, dt);
		update_hud_ui(doom);
		set_to_window(doom);
	}
	doom_exit_success(doom);
}

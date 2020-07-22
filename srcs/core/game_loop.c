#include "../../includes/doom.h"
#include "../../includes/audio.h"

#include <stdio.h>

void	doom_gui(t_doom *doom)
{
	(void)doom;
}

double	get_timeframe(long *last_frame_time)
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

void	game_loop(t_doom *doom)
{
	long			last_frame_time;
	double			dt;

	last_frame_time = 0;
	dt = 0.05; //leave for marin but remove before handing in
	doom->hud = TRUE; //this is to display only on game play
	while (doom->is_running == TRUE) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		dt = get_timeframe(&last_frame_time);
		doom_update(doom, dt);
		if (doom->game_editor == FALSE)
		{
			// sprite_reset(doom);
			doom_render(doom);
			audio(doom->audio, &doom->own_event);
			doom_gui(doom);
			sliding_door(doom, -1); //move to its own file
		}
		else
		{
			open_game_editor(doom);
		}
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
	doom_exit_success(doom);
}

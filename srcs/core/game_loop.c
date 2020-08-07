#include "../../includes/doom.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

#include <stdio.h>

static void	set_to_window(t_doom *doom)
{
	SDL_UpdateWindowSurface(doom->window);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

void		doom_gui(t_doom *doom)
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

void			game_loop(t_doom *doom)
{
	long			last_frame_time;
	double			dt;
	// int				counter = 1;

	// if (counter == 1)
	// 	printf("before sprite saved line: %f, %f --- %f, %f    line: %f, %f ---  %f, %f \n", doom->tests.start.x, doom->tests.start.y, doom->tests.end.x, doom->tests.end.y, doom->lib.sidedef[20].line.start.x, doom->lib.sidedef[20].line.start.y, doom->lib.sidedef[20].line.end.x, doom->lib.sidedef[20].line.end.y);
	// counter++;
	last_frame_time = 0;
	dt = 0.05; //leave for marin but remove before handing in
	while (doom->is_running == TRUE) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		dt = get_timeframe(&last_frame_time);
		doom_update(doom, dt);
		if (doom->game_editor == FALSE)
		{
			sprite_reset(doom);
			// if (counter == 1)
			// 	printf("saved line: %f, %f --- %f, %f    line: %f, %f ---  %f, %f \n", doom->tests.start.x, doom->tests.start.y, doom->tests.end.x, doom->tests.end.y, doom->lib.sidedef[20].line.start.x, doom->lib.sidedef[20].line.start.y, doom->lib.sidedef[20].line.end.x, doom->lib.sidedef[20].line.end.y);
			// counter++;
			doom_render(doom);
			sprite_render(doom);
			audio(doom->audio, &doom->own_event);
			doom_gui(doom);
			groceries(doom);
			sliding_door(doom, -1); //move to its own file
			// add_infection(doom); //move to a seprate file
		}
		else
			open_game_editor(doom);
		update_hud(doom);
		set_to_window(doom);
	}
	doom_exit_success(doom);
}

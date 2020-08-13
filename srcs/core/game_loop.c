#include "../../includes/doom.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"

static void		set_to_window(t_doom *doom)
{
	SDL_UpdateWindowSurface(doom->window);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

void			doom_gui(t_doom *doom)
{
	(void)doom;
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

void				game_loop(t_doom *doom)
{
	long			last_frame_time;
	double			dt;

	last_frame_time = 0;
	dt = 0.05; //leave for marin but remove before handing in
	while (doom->is_running == TRUE) // eventually only message bus will be in this loop. with SDL_UpdateWindowSurface and ft_bzero
	{
		timer(doom);
		dt = get_timeframe(&last_frame_time);
		// printf("before doom_update\n");
		doom_update(doom, dt);
		// printf("after doom_update\n");
		if (doom->game_editor == FALSE && doom->menu->game_over == FALSE)
		{
			sprite_reset(doom);
			// printf("before doom_renderyes\n");
			doom_render(doom);
			// printf("after doom_render\n");
			// audio(doom->audio, &doom->own_event);
			// doom_gui(doom);
			groceries(doom);
			// shooting(doom);
			sliding_door(doom, -1); //move to its own file
			// add_infection(doom); //move to a seprate file
		}
		else if (doom->game_editor == TRUE && doom->menu->game_over == FALSE)
			open_game_editor(doom);
		// printf("before update hud ui\n");
		update_hud_ui(doom);
		// printf("after update hud ui\n");
		set_to_window(doom);
	}
	doom_exit_success(doom);
}

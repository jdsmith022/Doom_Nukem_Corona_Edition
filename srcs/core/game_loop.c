#include "../../includes/doom.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/action.h"

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
		// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
			// printf("before timer\n");
		timer(doom);
		// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
			// printf("after timer\n");
		dt = get_timeframe(&last_frame_time);
		// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
			// printf("after get time frame\n");
		if (doom->game_editor == FALSE && doom->menu->game_over == FALSE)
		{
			// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
				// printf("before sprite reset\n");
			sprite_reset(doom);
			// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
				// printf("after sprite reset\n");
			doom_render(doom);
			// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
				// printf("after doom render\n");
			audio(doom, &doom->own_event);
			doom_gui(doom);
			groceries(doom);
		}
		else if (doom->game_editor == TRUE && doom->menu->game_over == FALSE)
			open_game_editor(doom);
		doom_update(doom, dt);
		// printf("einde update\n");
		update_hud_ui(doom);
		// printf("after update hud ui\n");
		set_to_window(doom);
		// printf("after set to window\n");
	}
	doom_exit_success(doom);
}

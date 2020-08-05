#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void	print_background(t_doom *doom)
{
	Uint32 *pixels;
	int		x;
	int		y;

	pixels = doom->surface->pixels;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = 0x00002E;
			y++;
		}
		x++;
	}
}

void	doom_start(t_doom *doom)
{
	long			last_frame_time;
	double			dt;

	last_frame_time = 0;
	dt = 0.05; //leave for marin but remove before handing in
	while (doom->menu->menu == TRUE)
	{
		dt = get_timeframe(&last_frame_time);
		mouse_settings(doom, dt);
		print_background(doom);
		start_menu_font(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
	doom->own_event.select = FALSE;
}

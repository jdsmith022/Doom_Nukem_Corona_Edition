#include "../../includes/doom.h"

// static void		update_values(t_doom *doom)
// {

// }

static void	draw_hud_top_bar(t_doom *doom)
{
	Uint32	*pixels;
	int		x;
	int		y;

	x = 0;
	pixels = doom->surface->pixels;
	while (x < WIDTH)
	{
		y = 0;
		while (y < 55)
		{
			if (y >= 0 && y <= 49 && x >= 0 && x <= WIDTH)
				pixels[(y * WIDTH + x)] = 0x00002E;
			else if (y > 49 && y < 53 && x >= 0 && x <= WIDTH)
				pixels[(y * WIDTH + x)] = 0x565659;
			else if (y >= 53 && y <= 55 && x >= 0 && x <= WIDTH)
				pixels[(y * WIDTH + x)] = 0x00000;
			y++;
		}
		x++;
	}
}

static void	draw_hud_bottom_bar(t_doom *doom)
{
	Uint32	*pixels;
	int		x;
	int		y;

	x = 0;
	pixels = doom->surface->pixels;
	while (x < WIDTH)
	{
		y = HEIGHT - 55;
		while (y < HEIGHT)
		{
			if (y >= HEIGHT - 55 && y < HEIGHT - 53 && \
			x >= 0 && x <= WIDTH)
				pixels[(y * WIDTH + x)] = 0x00000;
			else if (y >= HEIGHT - 53 && y < HEIGHT - 49 &&\
			x >= 0 && x <= WIDTH)
				pixels[(y * WIDTH + x)] = 0x565659;
			else if (y >= HEIGHT - 49 && \
			x >= 0 && x <= WIDTH && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = 0x00002E;
			y++;
		}
		x++;
	}
}

void		update_hud(t_doom *doom)
{
	if (doom->game_editor == FALSE)
	{
		draw_hud_top_bar(doom);
		draw_hud_bottom_bar(doom);
		// update_values(doom);
	}
	font_to_screen(doom);
}

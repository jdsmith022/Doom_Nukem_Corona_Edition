#include "../../includes/doom.h"

static void	draw_hud_background(t_doom *doom)
{
	int x;
	int y;
	Uint32 color;
	Uint32	*pixels;
	Uint32	limit;

	x = 0;
	limit = WIDTH / 4;
	color = 0x00002E;
	pixels = doom->surface->pixels;
	while (x < WIDTH)
	{
		y = HEIGHT - 60;
		while (x >= limit && x <= limit * 3)
			x++;
		while (y < HEIGHT - 10)
		{
			if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = color;
			y++;
		}
		x++;
	}
}

void		update_hud(t_doom *doom)
{
	if (doom->game_editor == FALSE)
		draw_hud_background(doom);
	font_to_screen(doom);
}

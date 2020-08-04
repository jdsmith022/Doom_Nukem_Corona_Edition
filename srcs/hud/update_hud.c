#include "../../includes/doom.h"

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
			x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = 0x00000;
			else if (y > HEIGHT - 53 && HEIGHT < HEIGHT - 49)
			{
				printf("here\n");
				pixels[(y * WIDTH + x)] = 0x616169;
			}
			else if ( y > HEIGHT - 49 && \
			 x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
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
		// draw_hud_bottom_top(doom);
		draw_hud_bottom_bar(doom);
	}
	font_to_screen(doom);
}

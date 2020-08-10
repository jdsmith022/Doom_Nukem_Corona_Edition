#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

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
			else if (y > 4 && y < 53 && x >= 0 && x <= WIDTH - 49)
				pixels[(y * WIDTH + x)] = 0x565659;
			else if (y >= 53 && y <= 55 && x >= 0 && x <= WIDTH - 49)
				pixels[(y * WIDTH + x)] = 0x00000;
			y++;
		}
		x++;
	}
}

static void	draw_side(Uint32 *pixels, int x, int y)
{
	if (y >= 49 && y < HEIGHT - 55 && x >= 0 && x <= 49)
		pixels[(y * WIDTH + x)] = 0x00002E;
	else if (y >= 49 && y < HEIGHT - 55 && x >= WIDTH - 49 && x <= WIDTH)
		pixels[(y * WIDTH + x)] = 0x00002E;
	else if (y >= 50 && y < HEIGHT - 49 && x < WIDTH - 49 && x >= WIDTH - 53)
		pixels[(y * WIDTH + x)] = 0x565659;
	else if (y >= 50 && y < HEIGHT - 49 && x > 49 && x <= 53)
		pixels[(y * WIDTH + x)] = 0x565659;
	else if (y >= 55 && y < HEIGHT - 55 && x < WIDTH - 53 && x >= WIDTH - 55)
		pixels[(y * WIDTH + x)] = 0x000000;
	else if (y >= 55 && y < HEIGHT - 55 && x > 53 && x <= 55)
		pixels[(y * WIDTH + x)] = 0x000000;
}

static void	draw_hud_side_bar(t_doom *doom)
{
	Uint32	*pixels;
	int		x;
	int		y;

	x = 0;
	pixels = doom->surface->pixels;
	while (x < WIDTH)
	{
		y = 49;
		while (y < HEIGHT)
		{
			draw_side(pixels, x, y);
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
			if (y >= HEIGHT - 53 && y < HEIGHT - 49 &&\
			x >= 50 && x <= WIDTH - 50)
				pixels[(y * WIDTH + x)] = 0x565659;
			else if (y >= HEIGHT - 55 && y < HEIGHT - 53 && \
			x >= 55 && x <= WIDTH - 55)
				pixels[(y * WIDTH + x)] = 0x00000;
			else if (y >= HEIGHT - 55 && \
			x >= 0 && x <= WIDTH && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = 0x00002E;
			y++;
		}
		x++;
	}
}

void		update_hud(t_doom *doom)
{
	if (doom->game_editor == FALSE && doom->menu->game_over == FALSE)
	{
		draw_hud_top_bar(doom);
		draw_hud_bottom_bar(doom);
		draw_hud_side_bar(doom);
		if (calculate_hud_levels(doom) == 1)
			update_hud_levels(doom, doom->lib.font_lib.hud_font);
		update_timer(doom, doom->lib.font_lib.hud_font);
	}
	if (doom->menu->game_over == FALSE)
		font_to_screen(doom);
}

#include "../../includes/doom.h"
#include "game_editor.h"

#include <stdio.h>

void	draw_portal(t_doom *doom, Uint32 **pixels, int sector)
{
	int 	x_dif;
	int		y_dif;
	double	x_steps;
	double	y_steps;
	double	i;
	double	x;
	double 	y;

	for(int b = SECTOR[sector].i_sidedefs; b < SECTOR[sector].i_sidedefs + SECTOR[sector].n_sidedefs; b++)
	{
		x_dif = (SIDEDEF[b].line.end.x) - (SIDEDEF[b].line.start.x);
		y_dif = (SIDEDEF[b].line.end.y) - (SIDEDEF[b].line.start.y);
		x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
		y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
		x = SIDEDEF[b].line.start.x - SECTOR[EDIT.cur_sec].diff_x;
		y = SIDEDEF[b].line.start.y - SECTOR[EDIT.cur_sec].diff_y;
		i = 0.0;
		while ((int)i < abs(x_dif) + abs(y_dif))
		{
			if ((int)y * WIDTH + (int)x > 0 && (int)y * WIDTH + (int)x < WIDTH * HEIGHT)
				pixels[0][((int)y * WIDTH) + (int)x] = 0xff696969;
			x += x_steps * 2;
			y += y_steps * 2;
			i += fabs(x_steps) * 2 + fabs(y_steps) * 2;
		}
	}
}

void	draw_lines(t_doom *doom, Uint32 **pixels, int b)
{
	int 	x_dif;
	int		y_dif;
	double	x_steps;
	double	y_steps;
	double	i;
	double	x;
	double 	y;

	x_dif = (SIDEDEF[b].line.end.x) - (SIDEDEF[b].line.start.x);
	y_dif = (SIDEDEF[b].line.end.y) - (SIDEDEF[b].line.start.y);
	x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
	x = SIDEDEF[b].line.start.x - SECTOR[EDIT.cur_sec].diff_x;
	y = SIDEDEF[b].line.start.y - SECTOR[EDIT.cur_sec].diff_y;
	i = 0.0;
	(void)*pixels;
	if (SIDEDEF[b].opp_sidedef != -1)
			draw_portal(doom, pixels, SIDEDEF[b].opp_sector);
	while ((int)i < abs(x_dif) + abs(y_dif))
	{
		if ((int)y * WIDTH + (int)x > 0 && (int)y * WIDTH + (int)x < WIDTH * HEIGHT)
		{
			if (SIDEDEF[b].opp_sidedef != -1 && EDIT.cur_sd != b)
			{
				pixels[0][((int)y * WIDTH) + (int)x] = 0xffFFA07A;
				pixels[0][((int)(y + 1) * WIDTH) + (int)x] = 0xffFFA07A;
				pixels[0][((int)y * WIDTH) + (int)x + 1] = 0xffFFA07A;
			}
			else if (EDIT.cur_sd != b)
			{
				pixels[0][((int)y * WIDTH) + (int)x] = 0x8c3cde6;
				pixels[0][((int)(y + 1) * WIDTH) + (int)x] = 0x8c3cde6;
				pixels[0][((int)y * WIDTH) + (int)x + 1] = 0x8c3cde6;
			}
			else
			{
				pixels[0][((int)y * WIDTH) + (int)x] = 0xff4287f5;
				pixels[0][((int)(y + 1) * WIDTH) + (int)x] = 0xff4287f5;
				pixels[0][((int)y * WIDTH) + (int)x + 1] = 0xff4287f5;
			}
		}
		x += x_steps;
		y += y_steps;
		i += fabs(x_steps) + fabs(y_steps);
	}
}

void	open_game_editor(t_doom *doom)
{
	Uint32	*pixels;
	int		i;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->distance = 1;
	pixels = doom->surface->pixels;
	if (SECTOR == NULL)
		init_game_design(doom);
	draw_screen_colors(pixels, doom);
	draw_images(pixels, doom);
	bars(&pixels, doom);
	i = SECTOR[EDIT.cur_sec].i_sidedefs;
	while (i < SECTOR[EDIT.cur_sec].i_sidedefs\
		+ SECTOR[EDIT.cur_sec].n_sidedefs)
	{
		draw_lines(doom, &pixels, i);
		i++;
	}
}

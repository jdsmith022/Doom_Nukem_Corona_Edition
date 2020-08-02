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

	for(int b = doom->game_design.sector[sector].i_sidedefs; b < doom->game_design.sector[sector].i_sidedefs + doom->game_design.sector[sector].n_sidedefs; b++)
	{
		x_dif = (doom->game_design.sidedef[b].line.end.x) - (doom->game_design.sidedef[b].line.start.x);
		y_dif = (doom->game_design.sidedef[b].line.end.y) - (doom->game_design.sidedef[b].line.start.y);
		x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
		y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
		x = doom->game_design.sidedef[b].line.start.x - doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		y = doom->game_design.sidedef[b].line.start.y - doom->game_design.sector[doom->game_design.cur_sec].diff_y;
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

	x_dif = (doom->game_design.sidedef[b].line.end.x) - (doom->game_design.sidedef[b].line.start.x);
	y_dif = (doom->game_design.sidedef[b].line.end.y) - (doom->game_design.sidedef[b].line.start.y);
	x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
	x = doom->game_design.sidedef[b].line.start.x - doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	y = doom->game_design.sidedef[b].line.start.y - doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	i = 0.0;
	(void)*pixels;
	if (doom->game_design.sidedef[b].opp_sidedef != -1)
			draw_portal(doom, pixels, doom->game_design.sidedef[b].opp_sector);
	while ((int)i < abs(x_dif) + abs(y_dif))
	{
		if ((int)y * WIDTH + (int)x > 0 && (int)y * WIDTH + (int)x < WIDTH * HEIGHT)
		{
			if (doom->game_design.sidedef[b].opp_sidedef != -1 && doom->game_design.cur_sd != b)
			{
				pixels[0][((int)y * WIDTH) + (int)x] = 0xffFFA07A;
				pixels[0][((int)(y + 1) * WIDTH) + (int)x] = 0xffFFA07A;
				pixels[0][((int)y * WIDTH) + (int)x + 1] = 0xffFFA07A;
			}
			else if (doom->game_design.cur_sd != b)
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


void	init_game_design(t_doom *doom)
{
	doom->game_design.sector = (t_sector*)malloc(sizeof(t_sector) * 2);
	doom->game_design.s_size = 2;
	doom->game_design.s_len = 0;
	doom->game_design.cur_sec = 0;
	doom->game_design.cur_sd = -1;
	doom->game_design.pl_pos = 0;
	doom->game_design.pl_sec = 0;
	doom->game_design.w_len = 0;
	doom->game_design.s_len = 0;
	doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].i_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_y = 0;
	doom->game_design.sector[doom->game_design.s_len].outside = 0;
	doom->game_design.sector[doom->game_design.s_len].light_level = 10;
	doom->game_design.portal_sec = -1;
	doom->game_design.portal_sd = -1;
	doom->game_design.b_sector = FALSE;
	doom->game_design.b_sidedef = FALSE;
	doom->game_design.b_object = FALSE;
}

void	open_game_editor(t_doom *doom)
{
	Uint32	*pixels;
	int		i;

	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->distance = 1;
	pixels = doom->surface->pixels;
	if (doom->game_design.sector == NULL)
		init_game_design(doom);
	draw_screen_colors(pixels, doom);
	draw_images(pixels, doom);
	if (doom->game_design.b_sector == TRUE)
		bars(&pixels, doom);
	i = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
	while (i < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs\
		+ doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
	{
		draw_lines(doom, &pixels, i);
		i++;
	}
}

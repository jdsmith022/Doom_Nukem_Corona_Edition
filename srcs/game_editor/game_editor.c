#include "../../includes/doom.h"
#include "game_editor.h"

#include <stdio.h>

t_sector *cpy_sector(t_sector *sector, int *s_size)
{
	t_sector	*new;
	int			i;

	new = (t_sector*)malloc(sizeof(t_sector) * *s_size * 2);
	i = 0;
	while (i < *s_size)
	{
		new[i] = sector[i];
		i++;
	}
	free(sector);
	*s_size *= 2;
	return (new);
}


void	add_sector(t_doom *doom)
{

		if (doom->game_design.s_len + 1 == doom->game_design.s_size)
				doom->game_design.sector = cpy_sector(doom->game_design.sector, &doom->game_design.s_size);
		printf("%i %i\n", doom->game_design.s_len, doom->game_design.s_size);
		doom->game_design.s_len++;
		doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].i_sidedefs = doom->game_design.w_len;
		doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
}

t_sidedef *cpy_sidedef(t_sidedef *sidedef, int *w_size)
{
	t_sidedef	*new;
	int			i;

	new = (t_sidedef*)malloc(sizeof(t_sidedef) * *w_size * 2);
	i = 0;
	while (i < *w_size)
	{
		new[i] = sidedef[i];
		i++;
	}
	free(sidedef);
	*w_size *= 2;
	return (new);
}

void 	mv_sidedef(t_sidedef **sidedef, int w_len, int id)
{
	int i;
	t_sidedef safe;
	t_sidedef safe2;

	i = id;
	safe = sidedef[0][i];
	sidedef[0][i] = sidedef[0][w_len];
	i++;
	while (i < w_len)
	{
		safe2 = sidedef[0][i];
		sidedef[0][i] = safe;
		safe = safe2;
		i++;
	}
	sidedef[0][i] = safe;
}


void	add_sidedef(t_doom *doom, int x, int y)
{
	static int start;
	int i;

	if (doom->game_design.sidedef == NULL)
	{
		doom->game_design.sidedef = (t_sidedef*)malloc(sizeof(t_sidedef) * 2);
		doom->game_design.w_size = 2;
		doom->game_design.w_len = 0;
	}
	if (!start)
	{
		if (doom->game_design.w_size < doom->game_design.w_len + 1)
				doom->game_design.sidedef = cpy_sidedef(doom->game_design.sidedef, &doom->game_design.w_size);
		doom->game_design.sidedef[doom->game_design.w_len].line.start.x = x;
		doom->game_design.sidedef[doom->game_design.w_len].line.start.y = y;
		start = 1;
	}
	else
	{
		doom->game_design.sidedef[doom->game_design.w_len].line.end.x = x;
		doom->game_design.sidedef[doom->game_design.w_len].line.end.y = y;
		doom->game_design.sidedef[doom->game_design.w_len].id = doom->game_design.w_len;
		if (doom->game_design.cur_sec != doom->game_design.s_len)
			mv_sidedef(&doom->game_design.sidedef, doom->game_design.w_len, doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs);
		i = doom->game_design.cur_sec + 1;
		while (i <= doom->game_design.s_len)
		{
			doom->game_design.sector[i].i_sidedefs++;
			i++;
		}
		doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs++;
		doom->game_design.w_len++;
		start = 0;
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

	x_dif = doom->game_design.sidedef[b].line.end.x - doom->game_design.sidedef[b].line.start.x;
	y_dif = doom->game_design.sidedef[b].line.end.y - doom->game_design.sidedef[b].line.start.y;
	x_steps = (float)x_dif / (float)(abs(x_dif) + abs(y_dif));
	y_steps = (float)y_dif / (float)(abs(x_dif) + abs(y_dif));
	x = doom->game_design.sidedef[b].line.start.x;
	y = doom->game_design.sidedef[b].line.start.y;
	i = 0.0;
	(void)*pixels;
	while ((int)i < abs(x_dif) + abs(y_dif))
	{
		pixels[0][((int)y * WIDTH) + (int)x] = 0x8c3cde6;
		pixels[0][((int)(y + 1) * WIDTH) + (int)x] = 0x8c3cde6;
		// pixels[0][((int)(y + 2) * WIDTH) + (int)x] = 0x8c3cde6;
		pixels[0][((int)y * WIDTH) + (int)x + 1] = 0x8c3cde6;
		// pixels[0][((int)y * WIDTH) + (int)x + 2] = 0x8c3cde6;
		x += x_steps;
		y += y_steps;
		i += fabs(x_steps) + fabs(y_steps);
	}
}

void	put_images(Uint32 **pixels, int x, int y, int img)
{
	int save_x;
	int sx;

	save_x = x;
	sx = 0;
	while (sx < FRAME_WIDTH * FRAME_HEIGHT)
	{
		pixels[0][((y * WIDTH) + x)] = editor_sprites[img][sx];
		sx++;
		x++;
		if (sx % FRAME_WIDTH == 0)
		{
			x = save_x;
			y++;
		}
	}
}

void    open_game_editor(t_doom *doom)
{
	Uint32 *pixels;

	if (doom->game_design.sector == NULL)
	{
		doom->game_design.sector = (t_sector*)malloc(sizeof(t_sector) * 2);
		doom->game_design.s_size = 2;
		doom->game_design.s_len = 0;
		doom->game_design.cur_sec = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
		doom->game_design.sector[doom->game_design.s_len].i_sidedefs = 0;

	}
	pixels = doom->surface->pixels;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x < WIDTH - (WIDTH / 5) && x > WIDTH / 5)
			{
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == 0)
					pixels[((y * WIDTH) + x)] = 0;
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == -45)
					pixels[((y * WIDTH) + x)] = 0xff6e2020;
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == 45)
					pixels[((y * WIDTH) + x)] = 0xff065535;
			}
			else
				pixels[((y * WIDTH) + x)] = 0x8c3cde6;

		}
	}
	put_images(&pixels, MINUS_X, MINUS_Y, minus);
	put_images(&pixels, PLUS_X, PLUS_Y, plus);
	put_images(&pixels, D_45_X, D_45_Y, d_45);
	put_images(&pixels, STRAIGHT_X, STRAIGHT_Y, straight);
	put_images(&pixels, D_M45_X, D_M45_Y, d_m45);
	put_images(&pixels, AR_LEFT_X, AR_LEFT_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_X, AR_RIGHT_Y, arrow_right);
	draw_bar(&pixels, BAR_X, BAR_Y, BAR_LEN);
	draw_bar_point(&pixels, doom, BAR_X, BAR_Y, BAR_LEN);
	for(int x = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs; x < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs; x++)
		draw_lines(doom, &pixels, x);


		// for(int x = 0; x < doom->game_design.w_len; x++)
		// draw_lines(doom, &pixels, x);
}
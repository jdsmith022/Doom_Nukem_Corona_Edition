#include "../../includes/doom.h"
#include "game_editor.h"

#include <stdio.h>

int			portal_count(t_sidedef *sidedef, int start, int end)
{
	int count;

	count = 0;
	while (start < end)
	{
		if (sidedef[start].opp_sidedef != -1)
			count++;
		start++;
	}
	return (count);
}

void		add_portal(t_doom *doom, int dir)
{
	static int diff_x;
	static int diff_y;

	if (dir != 0)
	{
		// if (portal_count(doom->game_design.sidedef, doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs, doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs) == 1)
		// {
		// 	for(int x = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs; x < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs; x++)
		// 	{
		// 		if (x != doom->game_design.cur_sd)
		// 		{
		// 			doom->game_design.sidedef[x].line.start.x -= doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		// 			doom->game_design.sidedef[x].line.start.y -= doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		// 			doom->game_design.sidedef[x].line.end.x -= doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		// 			doom->game_design.sidedef[x].line.end.y -= doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		// 		}
		// 	}
		// 	doom->game_design.sector[doom->game_design.cur_sec].diff_x = 0;
		// 	doom->game_design.sector[doom->game_design.cur_sec].diff_y = 0;
		// }
		del_sidedef(doom);
		doom->game_design.cur_sec += dir;
		if (doom->game_design.portal_sec == doom->game_design.cur_sec)
			doom->game_design.cur_sec += dir;
		if (doom->game_design.cur_sec < 0)
			doom->game_design.cur_sec = doom->game_design.s_len;
		if (doom->game_design.cur_sec > doom->game_design.s_len)
			doom->game_design.cur_sec = 0;
		if (doom->game_design.portal_sec == doom->game_design.cur_sec)
			doom->game_design.cur_sec += dir;
		doom->game_design.sector[doom->game_design.cur_sec].diff_x = diff_x;
		doom->game_design.sector[doom->game_design.cur_sec].diff_y = diff_y;
	}
	else
	{
		doom->game_design.portal_sd = doom->game_design.cur_sd;
		doom->game_design.portal_sec = doom->game_design.cur_sec;
		doom->game_design.cur_sec = doom->game_design.cur_sec > 0 ? doom->game_design.cur_sec - 1 : doom->game_design.s_len;
	}
	add_sidedef(doom,  doom->game_design.sidedef[doom->game_design.portal_sd].line.start.x, doom->game_design.sidedef[doom->game_design.portal_sd].line.start.y);
	add_sidedef(doom,  doom->game_design.sidedef[doom->game_design.portal_sd].line.end.x, doom->game_design.sidedef[doom->game_design.portal_sd].line.end.y);
	doom->game_design.sidedef[doom->game_design.portal_sd].opp_sidedef = doom->game_design.cur_sd;
	doom->game_design.sidedef[doom->game_design.portal_sd].opp_sector = doom->game_design.cur_sec;
	doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef = doom->game_design.portal_sd;
	doom->game_design.sidedef[doom->game_design.cur_sd].opp_sector = doom->game_design.portal_sec;
	diff_x = doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	diff_y = doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	doom->game_design.sector[doom->game_design.cur_sec].diff_x = doom->game_design.sector[doom->game_design.portal_sec].diff_x;
	doom->game_design.sector[doom->game_design.cur_sec].diff_y = doom->game_design.sector[doom->game_design.portal_sec].diff_y;
	// if (doom->game_design.sector[doom->game_design.cur_sec].diff_x == 0)
	// {
	// 	// doom->game_design.sector[doom->game_design.cur_sec].diff_x = 0;
	// 	// doom->game_design.sector[doom->game_design.cur_sec].diff_y = 0;
	// 	printf("%i %i \n", doom->game_design.sector[doom->game_design.cur_sec].diff_x, doom->game_design.sector[doom->game_design.cur_sec].diff_y);
	// 	for(int x = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs; x < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs; x++)
	// 	{
	// 		if (x != doom->game_design.cur_sd)
	// 		{
	// 			printf("pfr\n");
	// 			doom->game_design.sidedef[x].line.start.x += doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	// 			doom->game_design.sidedef[x].line.start.y += doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	// 			doom->game_design.sidedef[x].line.end.x += doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	// 			doom->game_design.sidedef[x].line.end.y += doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	// 		}
	// 	}
	// }

		


}

void		del_sector(t_doom *doom)
{
	int i;
	int n_sidedef;


	i = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
	while (i < doom->game_design.w_len - doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
	{
		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs];
		i++;
	}
	printf("%i %i\n", doom->game_design.w_len, doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs);
	doom->game_design.w_len -= doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs;
	printf("%i\n", doom->game_design.w_len);
	i = doom->game_design.cur_sec;
	n_sidedef = doom->game_design.sector[i].n_sidedefs;
	while (i < doom->game_design.s_len)
	{
		doom->game_design.sector[i] = doom->game_design.sector[i + 1];
		doom->game_design.sector[i].i_sidedefs -= n_sidedef;
		printf("hello\n");
		i++;
	}
	if (doom->game_design.cur_sec == doom->game_design.s_len)
		doom->game_design.cur_sec--;
	doom->game_design.s_len--;
	doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
}

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
		doom->game_design.s_len++;
		doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].i_sidedefs = doom->game_design.w_len;
		doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_y = 0;

}

void		del_sidedef(t_doom *doom)
{
	int i;

	i = doom->game_design.cur_sec + 1;
	while (i <= doom->game_design.s_len)
	{
		doom->game_design.sector[i].i_sidedefs--;
		i++;
	}
	i = doom->game_design.cur_sd;
	while (i < doom->game_design.w_len - 1)
	{
		doom->game_design.sidedef[i] = doom->game_design.sidedef[i + 1];
		i++;
	}
	doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs--;
	doom->game_design.w_len--;
	doom->game_design.cur_sd--;
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
		doom->game_design.sidedef[doom->game_design.w_len].line.start.x = x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		doom->game_design.sidedef[doom->game_design.w_len].line.start.y = y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		start = 1;
	}
	else
	{
		doom->game_design.sidedef[doom->game_design.w_len].line.end.x = x + doom->game_design.sector[doom->game_design.cur_sec].diff_x;
		doom->game_design.sidedef[doom->game_design.w_len].line.end.y = y + doom->game_design.sector[doom->game_design.cur_sec].diff_y;
		doom->game_design.sidedef[doom->game_design.w_len].id = doom->game_design.w_len;
		doom->game_design.sidedef[doom->game_design.w_len].sector = doom->game_design.cur_sec;
		doom->game_design.sidedef[doom->game_design.w_len].opp_sidedef = -1;
		doom->game_design.sidedef[doom->game_design.w_len].opp_sector = -1;
		if (doom->game_design.cur_sec != doom->game_design.s_len)
			mv_sidedef(&doom->game_design.sidedef, doom->game_design.w_len, doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs);
		i = doom->game_design.cur_sec + 1;
		while (i <= doom->game_design.s_len)
		{
			doom->game_design.sector[i].i_sidedefs++;
			i++;
		}
		doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs++;
		doom->game_design.cur_sd = doom->game_design.cur_sec != doom->game_design.s_len ? doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs : doom->game_design.w_len;
		doom->game_design.w_len++;
		start = 0;
	}
}

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
		x = doom->game_design.sidedef[b].line.start.x - doom->game_design.sector[sector].diff_x;
		y = doom->game_design.sidedef[b].line.start.y - doom->game_design.sector[sector].diff_y;
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
		doom->game_design.cur_sd = -1;
		doom->game_design.pl_pos = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
		doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
		doom->game_design.sector[doom->game_design.s_len].i_sidedefs = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
		doom->game_design.sector[doom->game_design.s_len].diff_y = 0;
		doom->game_design.portal_sec = -1;
		doom->game_design.portal_sd = -1;


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
	put_images(&pixels, AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right);
	put_images(&pixels, AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right);
	put_images(&pixels, AR_UP_M_X, AR_UP_M_Y, arrow_left);
	put_images(&pixels, AR_DOWN_M_X, AR_DOWN_M_Y, arrow_right);
	put_images(&pixels, CROSS_X, CROSS_Y, cross);
	put_images(&pixels, CROSS_P_X, CROSS_P_Y, cross);
	put_images(&pixels, PORTAL_X, PORTAL_Y, minus);
	put_images(&pixels, WALL_X, WALL_Y, plus);
	if (doom->game_design.portal_sec != -1)
	{
		put_images(&pixels, AR_LEFT_SC_X, AR_LEFT_SC_Y, arrow_left);
		put_images(&pixels, AR_RIGHT_SC_X, AR_RIGHT_SC_Y, arrow_right);
	}
	draw_bar(&pixels, BAR_X, BAR_Y, BAR_LEN);
	draw_bar_point(&pixels, doom, BAR_X, BAR_Y, BAR_LEN);
	for(int x = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs; x < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs; x++)
		draw_lines(doom, &pixels, x);


		// for(int x = 0; x < doom->game_design.w_len; x++)
		// draw_lines(doom, &pixels, x);
}
#include "../../includes/doom.h"

#include <stdio.h>

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

void	add_sidedef(t_doom *doom, int x, int y)
{
	static int start;

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
		pixels[0][((int)y * WIDTH) + (int)x] = 255000000;
		x += x_steps;
		y += y_steps;
		i += fabs(x_steps) + fabs(y_steps);
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
	}
	pixels = doom->surface->pixels;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (x < HEIGHT - 75)
				pixels[(y * WIDTH) + x] = 0;
			else
				pixels[(y * WIDTH) + x] = 100;

		}
	}
	for(int x = 0; x < doom->game_design.w_len; x++)
		draw_lines(doom, &pixels, x);
}
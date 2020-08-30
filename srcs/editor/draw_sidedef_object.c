#include "../../includes/doom.h"
#include "game_editor.h"

t_angle_line	calc_angle(t_line line, t_doom *doom)
{
	t_angle_line angle;

	angle.diff.x = (line.end.x) - (line.start.x);
	angle.diff.y = (line.end.y) - (line.start.y);
	angle.steps.x = (float)angle.diff.x / \
	(float)(abs(angle.diff.x) + abs(angle.diff.y));
	angle.steps.y  = (float)angle.diff.y / \
	(float)(abs(angle.diff.x) + abs(angle.diff.y));
	angle.start.x = line.start.x - \
	doom->game_design.sector[doom->game_design.cur_sec].diff_x;
	angle.start.y = line.start.y - \
	doom->game_design.sector[doom->game_design.cur_sec].diff_y;
	return (angle);
}

void			draw_portal(t_doom *doom, Uint32 **pixels, int sector)
{
	t_angle_line	angle;
	double			i;
	int				b;

	b = doom->game_design.sector[sector].i_sidedefs;
	while (b < doom->game_design.sector[sector].i_sidedefs \
	+ doom->game_design.sector[sector].n_sidedefs)
	{
		angle = calc_angle(doom->game_design.sidedef[b].line, doom);
		i = 0.0;
		while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
		{
			if ((int)angle.start.x < SIDEBAR_SIDEDEF && (int)angle.start.x >\
			SIDEBAR_SECTOR && (int)angle.start.y > 0 && \
			(int)angle.start.y < HEIGHT)
				pixels[0][((int)angle.start.y * WIDTH) +\
				(int)angle.start.x] = 0xff696969;
			angle.start.x += angle.steps.x * 2;
			angle.start.y += angle.steps.y * 2;
			i += fabs(angle.steps.x) * 2 + fabs(angle.steps.y) * 2;
		}
		b++;
	}
}

int				get_color(t_doom *doom, int b)
{
	int color;

	if (doom->game_design.sidedef[b].opp_sidedef != -1 &&\
	doom->game_design.cur_sd != b)
		color = 0xffFFA07A;
	else if (doom->game_design.cur_sd != b ||\
	doom->game_design.sidedef_bar == 0)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	return (color);
}

void			draw_lines(t_doom *doom, Uint32 **pixels, int b)
{
	t_angle_line	angle;
	double			i;
	int				color;

	angle = calc_angle(doom->game_design.sidedef[b].line, doom);
	i = 0.0;
	if (doom->game_design.sidedef[b].opp_sidedef != -1)
		draw_portal(doom, pixels, doom->game_design.sidedef[b].opp_sector);
	color = get_color(doom, b);
	while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
	{
		if ((int)angle.start.x < SIDEBAR_SIDEDEF &&\
		(int)angle.start.x > SIDEBAR_SECTOR 
		&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
		{
			pixels[0][((int)angle.start.y * WIDTH) + (int)angle.start.x]\
			= color;
			pixels[0][((int)(angle.start.y + 1) * WIDTH) + (int)angle.start.x]\
			= color;
			pixels[0][((int)angle.start.y * WIDTH) + (int)angle.start.x + 1] =\
			color;
		}
		angle.start.x += angle.steps.x;
		angle.start.y += angle.steps.y;
		i += fabs(angle.steps.x) + fabs(angle.steps.y);
	}
}

void			draw_object_side(t_doom *doom, Uint32 **pixels, int b, int side)
{
	double			i;
    int				color;
	t_angle_line	angle;

	angle = calc_angle(doom->game_design.object[b].lines[side], doom);
	i = 0.0;
	if (doom->game_design.cur_obj != b ||\
	doom->game_design.object_bar == 0)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
	{
		if ((int)angle.start.x < SIDEBAR_SIDEDEF && (int)angle.start.x > SIDEBAR_SECTOR 
		&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
		{
			pixels[0][((int)angle.start.y * WIDTH) + (int)angle.start.x] = color;
			pixels[0][((int)(angle.start.y + 1) * WIDTH) + (int)angle.start.x] = color;
			pixels[0][((int)angle.start.y * WIDTH) + (int)angle.start.x + 1] = color;
		}
		angle.start.x += angle.steps.x;
		angle.start.y += angle.steps.y;
		i += fabs(angle.steps.x) + fabs(angle.steps.y);
	}
}

void draw_object(t_doom *doom, Uint32 **pixels)
{
    int i;
    int side;

    i = doom->game_design.sector[doom->game_design.cur_sec].i_objects;
    while (i < doom->game_design.sector[doom->game_design.cur_sec].i_objects
		+ doom->game_design.sector[doom->game_design.cur_sec].n_objects)
	{
        side = 0;
        while (side < 4)
        {
		    draw_object_side(doom, pixels, i, side);
		    side++;
        }
        i++;
	}
}

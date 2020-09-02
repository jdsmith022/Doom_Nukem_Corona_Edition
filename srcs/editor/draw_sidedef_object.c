#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

t_angle_line		calc_angle(t_line line, t_doom *doom)
{
	t_angle_line angle;

	angle.diff.x = (line.end.x) - (line.start.x);
	angle.diff.y = (line.end.y) - (line.start.y);
	angle.steps.x = (float)angle.diff.x / (float)(abs(angle.diff.x) \
		+ abs(angle.diff.y));
	angle.steps.y = (float)angle.diff.y / (float)(abs(angle.diff.x) \
		+ abs(angle.diff.y));
	angle.start.x = line.start.x - \
		0;
	angle.start.y = line.start.y - \
		0;
	return (angle);
}

// static void			draw_portal(t_doom *doom, Uint32 **pixels, int sector)
// {
// 	t_angle_line	angle;
// 	double			i;
// 	int				b;

// 	b = doom->game_design.sector[sector].i_sidedefs;
// 	while (b < doom->game_design.sector[sector].i_sidedefs +\
// 		doom->game_design.sector[sector].n_sidedefs)
// 	{
// 		angle = calc_angle(doom->game_design.sidedef[b].line, doom);
// 		i = 0.0;
// 		while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
// 		{
// 			if ((int)angle.start.x < SIDEBAR_SIDEDEF && \
// 				(int)angle.start.x > SIDEBAR_SECTOR
// 			&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
// 				pixels[0][((int)angle.start.y * WIDTH) + \
// 					(int)angle.start.x] = 0xff696969;
// 			angle.start.x += angle.steps.x * 2;
// 			angle.start.y += angle.steps.y * 2;
// 			i += fabs(angle.steps.x) * 2 + fabs(angle.steps.y) * 2;
// 		}
// 		b++;
// 	}
// }

void				draw_lines(t_doom *doom, Uint32 **pixels,
						t_ed_sidedef *ed_sidedef)
{
	t_angle_line	angle;
	double			i;
	int				color;

	angle = calc_angle(ed_sidedef->line, doom);
	i = 0.0;
	// if (ed_sidedef->opp_sector != -1)
	// 	draw_portal(doom, pixels, \
	// 		ed_sidedef->opp_sector);
	if (ed_sidedef->opp_sector != -1 && \
	doom->game_design.cur_sd != ed_sidedef->id)
		color = 0xffFFA07A;
	else if (doom->game_design.cur_sd != ed_sidedef->id || \
		doom->game_design.sidedef_bar == 0)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
	{
		if ((int)angle.start.x < SIDEBAR_SIDEDEF && \
			(int)angle.start.x > SIDEBAR_SECTOR
		&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
			set_pixels(pixels, angle, color);
		set_angle(&angle, &i);
	}
}

// static void			draw_object_side(t_doom *doom, Uint32 **pixels,
// 						int b, int side)
// {
// 	double			i;
// 	int				color;
// 	t_angle_line	angle;

// 	angle = calc_angle(doom->game_design.object[b].lines[side], doom);
// 	i = 0.0;
// 	if (doom->game_design.cur_obj != b || doom->game_design.object_bar == 0)
// 		color = 0x8c3cde6;
// 	else
// 		color = 0xff4287f5;
// 	while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
// 	{
// 		if ((int)angle.start.x < SIDEBAR_SIDEDEF &&\
// 		(int)angle.start.x > SIDEBAR_SECTOR \
// 		&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
// 			set_pixels(pixels, angle, color);
// 		set_angle(&angle, &i);
// 	}
// }

// void				draw_object(t_doom *doom, Uint32 **pixels)
// {
// 	int		i;
// 	int		side;

// 	i = doom->game_design.sector[doom->game_design.cur_sec].i_objects;
// 	while (i < doom->game_design.sector[doom->game_design.cur_sec].i_objects\
// 		+ doom->game_design.sector[doom->game_design.cur_sec].n_objects)
// 	{
// 		side = 0;
// 		while (side < 4)
// 		{
// 			draw_object_side(doom, pixels, i, side);
// 			side++;
// 		}
// 		i++;
// 	}
// }

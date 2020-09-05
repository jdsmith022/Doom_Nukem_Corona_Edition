#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void				set_angle(t_angle_line *angle, double *i)
{
	angle->start.x += angle->steps.x;
	angle->start.y += angle->steps.y;
	*i += fabs(angle->steps.x) + fabs(angle->steps.y);
}

static void				put_pixel_sidedef(Uint32 **pixels,
							t_angle_line angle, int color)
{
	pixels[0][((int)angle.start.y * WIDTH) + \
		(int)angle.start.x] = color;
	pixels[0][((int)(angle.start.y + 1) * WIDTH) + \
		(int)angle.start.x] = color;
	pixels[0][((int)angle.start.y * WIDTH) + \
		(int)angle.start.x + 1] = color;
}

static t_angle_line		calc_angle(t_line line, t_doom *doom)
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

void					draw_ed_sidedef(t_doom *doom, Uint32 **pixels,
						t_ed_sidedef *ed_sidedef)
{
	t_angle_line	angle;
	double			i;
	int				color;

	angle = calc_angle(ed_sidedef->line, doom);
	i = 0.0;
	if (ed_sidedef->opp_sector != -1 && \
	doom->game_design.cur_sd != ed_sidedef->id)
		color = 0xffFFA07A;
	else if (doom->game_design.cur_sd != ed_sidedef->id)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	while ((int)i < abs(angle.diff.x) + abs(angle.diff.y))
	{
		if ((int)angle.start.x < SIDEBAR_SIDEDEF && \
			(int)angle.start.x > SIDEBAR_SECTOR
		&& (int)angle.start.y > 0 && (int)angle.start.y < HEIGHT)
			put_pixel_sidedef(pixels, angle, color);
		set_angle(&angle, &i);
	}
}

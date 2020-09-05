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

static void put_pixel(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= SIDEBAR_SECTOR && x <= SIDEBAR_SIDEDEF && y >= 0 && y <= HEIGHT)
		pixels[(y * WIDTH + x)] = color;
}

void				draw_lines(t_doom *doom, Uint32 **pixels,
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
			set_pixels(pixels, angle, color);
		set_angle(&angle, &i);
	}
}


static void			draw_object_side(t_doom *doom, Uint32 **pixels,
						t_ed_sprite *sprite, int side)
{
	double			i;
	int				color;
	int				x;
	int				y;
	t_line			line[4];

	i = 0.0;
	if (doom->game_design.cur_sprite != sprite->id || doom->game_design.object_bar == 0)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	x = sprite->pos.x - 5;
	y = sprite->pos.y - 5;
	while (x < sprite->pos.x + 5)
	{
		y = sprite->pos.y - 5;
		while ( y < sprite->pos.y + 5)
		{
			put_pixel(doom, x, y, color);
			y++;
		}
		x++;
	}
}

void				draw_object(t_doom *doom, Uint32 **pixels)
{
	t_ed_sprite *sprite;
	int		side;

	sprite = doom->game_design.sp_head->next;
	while (sprite != NULL)
	{
		draw_object_side(doom, pixels, sprite, side);
		sprite = sprite->next;
	}
}

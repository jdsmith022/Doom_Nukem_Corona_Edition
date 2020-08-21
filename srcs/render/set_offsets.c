#include "../../includes/doom.h"

int			sprite_offset(int x, int sprite_x)
{
	int		diff;

	diff = x - sprite_x;
	return (diff);
}	

void		wall_offset(t_plane *plane, int sidedef_top)
{
	plane->wall_offset = 0;
	if (sidedef_top < 0)
	{
		plane->wall_offset = abs(sidedef_top);
		plane->sidedef_top = 0;
	}
	else if (sidedef_top > HEIGHT)
		sidedef_top = HEIGHT;
	else
		plane->sidedef_top = sidedef_top;
}

Uint8			find_slope_line_offset(t_point start, t_point end)
{
	Uint8 max_x;
	Uint8 max_y;
	Uint8 diff;

	if (start.x >= end.x)
		max_x = start.x - end.x;
	else
		max_x = end.x - start.x;
	if (start.y >= end.y)
		max_y = start.y - end.y;
	else
		max_y = end.y - start.y;
	if (max_x <= max_y)
		diff = 1;
	else
		diff = 2;
	return (diff);
}

void				set_offset(t_sidedef *sidedef, t_sidedef curr_sidedef,
						t_point intersect, t_doom *doom)
{
	t_point start;
	t_point end;
	Uint8	diff;

	start = curr_sidedef.line.start;
	end = curr_sidedef.line.end;
	diff = find_slope_line_offset(start, end);
	if (start.x == end.x || diff == 1)
	{
		sidedef->offset = ft_rounder(intersect.y) % doom->texture_width;
		sidedef->dir = 0;
	}
	else if (start.y == end.y || diff == 2)
	{
		sidedef->offset = ft_rounder(intersect.x) % doom->texture_width;
		sidedef->dir = 1;
	}
}

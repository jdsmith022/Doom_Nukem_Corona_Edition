#include "../../includes/doom.h"
#include "../../includes/action.h"

static int	check_collision(t_doom *doom, t_sidedef sidedef,
				t_line move)
{
	if (sidedef.opp_sector == -1 || \
	check_floor_diff(doom, doom->i_sector, sidedef.opp_sector) == TRUE ||
	doom->own_event.scissor_lift == TRUE)
		return (-1);
	else if (check_sector_height_diff(doom, doom->i_sector, \
	sidedef.opp_sector) == FALSE)
		return (-1);
	else if (sidedef.distance < 2 && \
	(sidedef.opp_sector == -1 || sidedef.action == 2))
		return (-1);
	else if (sidedef.opp_sector != -1)
		doom->i_sector = sidedef.opp_sector;
	return (1);
}

static int	movement_intersection(t_doom *doom, t_line move, \
	int sector, double angle)
{
	int				x;
	t_sidedef		sidedef;
	static t_point	prev_intersect;

	x = doom->lib.sector[sector].i_sidedefs;
	while (x < doom->lib.sector[sector].n_sidedefs\
		+ doom->lib.sector[sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		sidedef.intersect = check_line_intersection(move, sidedef.line);
		sidedef.sector = sector;
		if (point_distance(sidedef.intersect, move.start, angle) < 20.0 && \
			sidedef.action == 2)
			sliding_door(NULL, x);
		if (((isnan(sidedef.intersect.x) == 0 && isnan(sidedef.intersect.y) == 0)) && \
			((sidedef.intersect.x != prev_intersect.x  && sidedef.intersect.y != prev_intersect.y)))
		{
			prev_intersect = sidedef.intersect;
			return (check_collision(doom, sidedef, move));
		}
		x++;
	}
	prev_intersect.x = 0;
	prev_intersect.y = 0;
	return (0);
}

void	cam_move_rl(t_doom *doom, double dt, double direction)
{
	t_line		movement;
	int			collision;
	t_sector	sector;

	sector = doom->lib.sector[doom->i_sector];
	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle + direction);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle + direction);
	if (sprite_collision(doom, movement) == 1)
		movement.end = doom->pos;
	collision = movement_intersection(doom, movement, doom->i_sector, \
		doom->dir_angle + direction);
	if (collision == 1)
	{
		collision = movement_intersection(doom, movement, doom->i_sector, \
			doom->dir_angle + direction);
		if (collision == 0)
			doom->pos = movement.end;
	}
	else if (collision == 0)
		doom->pos = movement.end;
}

void	cam_move_fb(t_doom *doom, double dt, double direction)
{
	t_line	movement;
	int		collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
	movement.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
	if (sprite_collision(doom, movement) == 1)
		movement.end = doom->pos;
	collision = movement_intersection(doom, movement, \
		doom->i_sector, doom->dir_angle);
	if (collision == 1)
	{
		collision = movement_intersection(doom, movement, doom->i_sector, \
			doom->dir_angle + direction);
		if (collision == 0)
			doom->pos = movement.end;
	}
	else if (collision == 0)
		doom->pos = movement.end;
}

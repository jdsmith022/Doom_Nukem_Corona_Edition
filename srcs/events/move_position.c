#include "../../includes/doom.h"
#include "../../includes/action.h"

static int			check_collision(t_doom *doom, t_sidedef sidedef,
				t_line move)
{
	if (sidedef.opp_sector == -1 || sidedef.action == 2)
		return (-1);
	if (check_floor_diff(doom, doom->i_sector, sidedef.opp_sector) == TRUE ||
	doom->own_event.scissor_lift == TRUE)
		return (-1);
	else if (check_sector_height_diff(doom, doom->i_sector, \
	sidedef.opp_sector) == FALSE)
		return (-1);
	return (0);
}

static t_sidedef	sidedef_intersection(t_doom *doom, t_line move, \
	int sector, t_point prev_intersect)
{
	int				x;
	t_sidedef		sidedef;

	x = doom->lib.sector[sector].i_sidedefs;
	while (x < doom->lib.sector[sector].n_sidedefs\
		+ doom->lib.sector[sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		sidedef.intersect = check_line_intersection(move, sidedef.line);
		if (((isnan(sidedef.intersect.x) == 0 && \
			isnan(sidedef.intersect.y) == 0)) && \
			((sidedef.intersect.x != prev_intersect.x && \
			sidedef.intersect.y != prev_intersect.y)))
			return (sidedef);
		x++;
	}
	return (sidedef);
}

static t_sidedef	check_move_sidedef_intersection(t_doom *doom, t_line move, \
	int sector, t_point prev_intersect)
{
	t_sidedef	sidedef;
	int			collision;

	sidedef = sidedef_intersection(doom, move, sector, prev_intersect);
	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
	{
		doom->i_sector = sector;
		doom->pos = move.end;
	}
	else
	{
		collision = check_collision(doom, sidedef, move);
		if (collision != -1)
		{
			prev_intersect = sidedef.intersect;
			sector = sidedef.opp_sector;
			check_move_sidedef_intersection(doom, move, sector, prev_intersect);
		}
	}
	return (sidedef);
}

static void			move_position(t_doom *doom, t_line move, double angle)
{
	t_sidedef	sidedef;
	t_point		prev_intersect;

	move.start = doom->pos;
	prev_intersect.x = -1;
	prev_intersect.y = -1;
	if (sprite_collision(doom, move) == 1)
		return ;
	sidedef = check_move_sidedef_intersection(doom, move, \
		doom->i_sector, prev_intersect);
	if (sidedef.action == 2 && point_distance(sidedef.intersect, \
		doom->pos, angle) < 20.0)
		sliding_door(NULL, sidedef.id);
}

void				set_new_position(t_doom *doom, t_event *event, double dt)
{
	t_line		move;
	double		angle;
	double		direction;

	if (event->move_pos_f == TRUE || event->move_pos_b == TRUE)
	{
		direction = MOVE_SPEED;
		if (event->move_pos_b == TRUE)
			direction = -MOVE_SPEED;
		move.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
		move.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
		angle = doom->dir_angle;
	}
	else if (event->move_pos_r == TRUE || event->move_pos_l == TRUE)
	{
		direction = 90 * PI / 180;
		if (event->move_pos_l == TRUE)
			direction = -90 * PI / 180;
		move.end.x = doom->pos.x + (MOVE_SPEED * dt) * \
			cos(doom->dir_angle + direction);
		move.end.y = doom->pos.y + (MOVE_SPEED * dt) * \
			sin(doom->dir_angle + direction);
		angle = doom->dir_angle + direction;
	}
	move_position(doom, move, angle);
}

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
	{
		doom->prev_sector = doom->i_sector;
		doom->i_sector = sidedef.opp_sector;
	}
	return (1);
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
		sidedef.sector = sector;
		if (((isnan(sidedef.intersect.x) == 0 && \
			isnan(sidedef.intersect.y) == 0)) && \
			((sidedef.intersect.x != prev_intersect.x && \
			sidedef.intersect.y != prev_intersect.y)))
			return (sidedef);
		x++;
	}
	return (sidedef);
}

static void		check_sliding_door(t_doom *doom, t_sidedef sidedef, \
	t_point pos, double direction)
{
	double	angle;

	if (direction == abs(MOVE_SPEED))
		angle = doom->dir_angle;
	else
		angle = doom->dir_angle + direction;
	if (point_distance(sidedef.intersect, pos, angle) < 20.0)
		sliding_door(NULL, sidedef.id);
}

static t_line	set_movement(t_doom *doom, double dt, double direction)
{
	t_line movement;

	movement.start = doom->pos;
	if (direction == MOVE_SPEED || direction == -MOVE_SPEED)
	{
		movement.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
		movement.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
	}
	else
	{
		movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle + direction);
		movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle + direction);
	}
	return (movement);
}

void	cam_move(t_doom *doom, double dt, double direction)
{
	t_line		movement;
	t_sidedef	sidedef;
	t_point		prev_intersect;
	int			collision;

	movement = set_movement(doom, dt, direction);
	prev_intersect.x = -1;
	prev_intersect.y = -1;
	if (sprite_collision(doom, movement) == 1)
		movement.end = doom->pos;
	sidedef = sidedef_intersection(doom, movement, doom->i_sector, prev_intersect);
	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
		doom->pos = movement.end;
	else
		collision = check_collision(doom, sidedef, movement);
	printf("1: sidef_id = %d, collision = %d\n", sidedef.id, collision);
	if (collision == 1)
	{
		prev_intersect = sidedef.intersect;
		sidedef = sidedef_intersection(doom, movement, doom->i_sector, prev_intersect);
		collision = check_collision(doom, sidedef, movement);
		printf("2: sidef_id = %d , collision = %d\n", sidedef.id, collision);
		if (collision == -1)
			doom->i_sector = doom->prev_sector;
		if (collision == 0)
			doom->pos = movement.end;
	}
	if (sidedef.action == 2)
		check_sliding_door(doom, sidedef, movement.start, direction);
}

//void	cam_move_fb(t_doom *doom, double dt, double direction)
//{
//	t_line	movement;
//	int		collision;

//	movement.start = doom->pos;
//	movement.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
//	movement.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
//	if (sprite_collision(doom, movement) == 1)
//		movement.end = doom->pos;
//	collision = movement_intersection(doom, movement, \
//		doom->i_sector, doom->dir_angle);
//	printf("1: collision = %d\n", collision);
//	if (collision == 1)
//	{
//		collision = movement_intersection(doom, movement, doom->i_sector, \
//			doom->dir_angle + direction);
//		if (collision == -1)
//			doom->i_sector = doom->prev_sector;
//		printf("2: collision = %d\n\n", collision);
//		if (collision == 0)
//			doom->pos = movement.end;
//	}
//	else if (collision == 0)
//		doom->pos = movement.end;
//}

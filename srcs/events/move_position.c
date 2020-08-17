#include "../../includes/doom.h"
#include "../../includes/action.h"

t_point		check_line_intersection(t_line move, t_sidedef sidedef,
				double angle, int x)
{
	t_point	intersect;
	t_point	move_delta;
	t_point sidedef_delta;

	move_delta = line_delta(move.start, move.end);
	sidedef_delta = line_delta(sidedef.line.start, sidedef.line.end);
	intersect = line_intersection(move.start, move_delta,\
	sidedef.line.start, sidedef_delta);
	if (point_distance(intersect, move.start, angle) < 20.0 && sidedef.action == 2)
		sliding_door(NULL, x);
	return (intersect);
}

static int	check_collision(t_doom *doom, t_sidedef sidedef,
				t_line move, t_point intersect)
{
	if (sidedef.opp_sector == -1 ||\
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
		doom->i_sector = sidedef.opp_sector;
		if (move.end.x == intersect.x && move.end.y == intersect.y)
			return (1);
	}
	return (0);
}

static int	movement_collision(t_doom *doom, t_line move, double angle)
{
	int			x;
	t_point		intersect;
	t_sidedef	sidedef;
	t_sidedef	opp_sidedef;

	x = doom->lib.sector[doom->i_sector].i_sidedefs;
	while (x < doom->lib.sector[doom->i_sector].n_sidedefs\
		+ doom->lib.sector[doom->i_sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		opp_sidedef = doom->lib.sidedef[sidedef.opp_sidedef];
		intersect = check_line_intersection(move, sidedef, angle, x);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
			return (check_collision(doom, sidedef, move, intersect));
		x++;
	}
	return (0);
}

void	cam_move_rl(t_doom *doom, double dt, int direction)
{
	t_line		movement;
	int			collision;
	t_sector	sector;

	collision = 0;
	sector = doom->lib.sector[doom->i_sector];
	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle + direction);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle + direction);
	if (sprite_collision(doom, movement) == 1)
	{
		doom->pos = movement.start;
		return ;
	}
		//movement.end = doom->pos;
	// if (sector.action == TROLLY && doom->own_event.trolly == FALSE)
		// movement.end = doom->pos;
	printf("after sprite_collision rl\n");
	collision = movement_collision(doom, movement, doom->dir_angle + direction);
	printf("after normal collision rl\n");
	if (collision != -1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += 5 * cos(doom->dir_angle + direction);
			doom->pos.y += 5 * sin(doom->dir_angle + direction);
		}
	}
	printf("end cam mov fb collision = %d\n", collision);
}

void	cam_move_fb(t_doom *doom, double dt, int direction)
{
	t_line	movement;
	int		collision;

	collision = 0;
	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle); //check movement end x and end y, am I hitting something?
	movement.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
	if (sprite_collision(doom, movement) == 1)
	{
		doom->pos = movement.start;
		return ;
	}
		// movement.end = doom->pos;
	printf("after sprite collision fb\n");
	collision = movement_collision(doom, movement, doom->dir_angle + direction);
	printf("after normal collision fb\n");
	if (collision != -1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += direction / 10 * cos(doom->dir_angle);
			doom->pos.y += direction / 10 * sin(doom->dir_angle);
		}
	}
	printf("end cam mov fb collision = %d\n", collision);
}

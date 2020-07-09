/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 10:54:54 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/03 13:50:12 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_point	check_line_intersection(t_line move, t_sidedef sidedef, double angle, int x)
{
	t_point	intersect;
	t_point	move_delta;
	t_point sidedef_delta;

	move_delta = line_delta(move.start, move.end);
	sidedef_delta = line_delta(sidedef.line.start, sidedef.line.end);
	intersect = line_intersection(move.start, move_delta,\
	sidedef.line.start, sidedef_delta);
	if (point_distance(intersect, move.start, angle) < 10.0 && sidedef.action == 1) //create_enum and than use the name
		sliding_door(NULL, x);
	return (intersect);
}

int		movement_collision(t_doom *doom, t_line move, double angle)
{
	int			x;
	t_point		intersect;
	t_sidedef	sidedef;

	x = doom->lib.sector[doom->i_sector].i_sidedefs;
	while (x < doom->lib.sector[doom->i_sector].n_sidedefs\
		+ doom->lib.sector[doom->i_sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		intersect = check_line_intersection(move, sidedef, angle, x);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			if (sidedef.opp_sector == -1 || check_floor_diff(doom, doom->i_sector, sidedef.opp_sector) == TRUE)
				return (-1);
			else if (sidedef.opp_sector != -1)
			{
				doom->i_sector = sidedef.opp_sector;
				if (move.end.x == intersect.x && move.end.y == intersect.y)
					return (1);
				return (0);
			}
		}
		x++;
	}
	return (0);
}

void	cam_move_rl(t_doom *doom, double dt, int direction)
{
	t_line	movement;
	int		collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle + direction);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle + direction);
	collision = movement_collision(doom, movement, doom->dir_angle + direction);
	if (collision != -1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += 5 * cos(doom->dir_angle + direction);
			doom->pos.y += 5 * sin(doom->dir_angle + direction);
		}
	}
}

void	cam_move_fb(t_doom *doom, double dt, int direction)
{
	t_line	movement;
	int		collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (direction * dt) * cos(doom->dir_angle);
	movement.end.y = doom->pos.y + (direction * dt) * sin(doom->dir_angle);
	collision = movement_collision(doom, movement,  doom->dir_angle + direction);
	if (collision != -1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += direction / 10 * cos(doom->dir_angle);
			doom->pos.y += direction / 10 * sin(doom->dir_angle);
		}
	}
}

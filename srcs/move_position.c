/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 10:54:54 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/07 17:23:58 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


t_point	check_line_intersection(t_line move, t_sidedef sidedef)
{
	t_point	intersect;
	t_point	move_delta;
	t_point sidedef_delta;

	move_delta = line_delta(move.start, move.end);
	sidedef_delta = line_delta(sidedef.start, sidedef.end);
	intersect = line_intersection(move.start, move_delta,\
	sidedef.start, sidedef_delta);
	return (intersect);
}

int		movement_collision(t_doom *doom, t_line move)
{
	int			x;
	t_point		intersect;
	t_sidedef 	sidedef;

	x = 0;
	while (x < doom->sector[doom->curr_sector].n_sidedefs)
	{
		sidedef = doom->sector[doom->curr_sector].sidedef[x];
		intersect = check_line_intersection(move, sidedef);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			if (sidedef.opp_sector == -1)
				return (-1);
			else if (sidedef.opp_sector != -1)
			{
				doom->curr_sector = sidedef.opp_sector;
				if (move.end.x == intersect.x || move.end.y == intersect.y)
					return (1);
			}
			return (0);
		}
		x++;
	}
	return (0);
}

void	move_position_right(t_doom *doom)
{
	t_line movement;
	double	qt_radian;
	int		collision;

	qt_radian = 90 * PI / 180;
	movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle - qt_radian);
	movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle - qt_radian);
	collision = movement_collision(doom, movement);
	if (collision == 0 || collision == 1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += 5 * cos(doom->dir_angle - qt_radian);
			doom->pos.y += 5* sin(doom->dir_angle - qt_radian);
		}

	}
}

void move_position_left(t_doom *doom)
{
	t_line movement;
	double	qt_radian;
	int		collision;

	qt_radian = 90 * PI / 180;
	movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle + qt_radian);
	movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle + qt_radian);
	collision = movement_collision(doom, movement);
	if (collision == 0 || collision == 1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += 5 * cos(doom->dir_angle + qt_radian);
			doom->pos.y += 5 * sin(doom->dir_angle + qt_radian);
		}
	}
}

void move_position_backwards(t_doom *doom)
{
	t_line 	movement;
	int 	collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x - SPEED * cos(doom->dir_angle);
	movement.end.y = doom->pos.y - SPEED * sin(doom->dir_angle);
	collision = movement_collision(doom, movement);
	if (collision == 0 || collision == 1)
	{
			doom->pos = movement.end;
			if (collision == 1)
			{
				doom->pos.x -= 5 * cos(doom->dir_angle);
				doom->pos.y -= 5 * sin(doom->dir_angle);
			}
	}
}


void move_position_forwards(t_doom *doom)
{
	t_line 	movement;
	int 	collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle);
	movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle);
	collision = movement_collision(doom, movement);
	if (collision == 0 || collision == 1)
	{
			doom->pos = movement.end;
			if (collision == 1)
			{
				doom->pos.x += 5 * cos(doom->dir_angle);
				doom->pos.y += 5 * sin(doom->dir_angle);
			}
	}
}



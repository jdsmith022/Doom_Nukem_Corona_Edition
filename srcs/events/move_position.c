/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 10:54:54 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/31 18:29:42 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	position_movement_r(t_doom *doom, time_t dt)
{
	t_line	movement;
	double	qt_radian;
	int		collision;

	qt_radian = 90 * PI / 180;
	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle + qt_radian);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle + qt_radian);
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

void	position_movement_l(t_doom *doom, time_t dt)
{
	t_line	movement;
	double	qt_radian;
	int		collision;

	qt_radian = 90 * PI / 180;
	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) *\
		cos(doom->dir_angle - qt_radian);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) *\
		sin(doom->dir_angle - qt_radian);
	collision = movement_collision(doom, movement);
	if (collision == 0 || collision == 1)
	{
		doom->pos = movement.end;
		if (collision == 1)
		{
			doom->pos.x += 5 * cos(doom->dir_angle - qt_radian);
			doom->pos.y += 5 * sin(doom->dir_angle - qt_radian);
		}
	}
}

void	position_movement_b(t_doom *doom, time_t dt)
{
	t_line	movement;
	int		collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x - (MOVE_SPEED * dt) * cos(doom->dir_angle);
	movement.end.y = doom->pos.y - (MOVE_SPEED * dt) * sin(doom->dir_angle);
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

void	position_movement_f(t_doom *doom, time_t dt)
{
	t_line	movement;
	int		collision;

	movement.start = doom->pos;
	movement.end.x = doom->pos.x + (MOVE_SPEED * dt) * cos(doom->dir_angle);
	movement.end.y = doom->pos.y + (MOVE_SPEED * dt) * sin(doom->dir_angle);
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

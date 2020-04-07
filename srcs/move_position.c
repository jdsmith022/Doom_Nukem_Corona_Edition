/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/07 10:54:54 by Malou          #+#    #+#                */
/*   Updated: 2020/04/07 12:18:43 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		movement_collision(t_doom *doom, t_line move)
{
	int		x;
	t_point	intersect;
	t_point	move_delta;
	t_point sidedef_delta;
	t_sidedef sidedef;

	x = 0;
	while (x < doom->sector[doom->curr_sector].n_sidedefs)
	{
		sidedef = doom->sector[doom->curr_sector].sidedef[x];
		move_delta = line_delta(move.start, move.end);
		sidedef_delta = line_delta(sidedef.start, sidedef.end);
		intersect = line_intersection(move.start, move_delta,\
			sidedef.start, sidedef_delta);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			if (sidedef.opp_sector == -1)
				return (-1);
			else if (sidedef.opp_sector != -1)
				doom->curr_sector = sidedef.opp_sector;
			return (0);
		}
		x++;
	}
	return (0);
}

t_line player_side_movement(t_doom *doom, int sym, t_line movement)
{
	double	qt_radian;

	qt_radian = 90 * PI / 180;
	if (sym == SDLK_a )
	{
		movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle - qt_radian);
		movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle - qt_radian);
	}
	else if (sym == SDLK_d)
	{
		movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle + qt_radian);
		movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle + qt_radian);
	}
	return (movement);
}

t_line player_movement(t_doom *doom, int sym, t_line movement)
{
	if (sym == SDLK_w)
	{
		movement.end.x = doom->pos.x + SPEED * cos(doom->dir_angle);
		movement.end.y = doom->pos.y + SPEED * sin(doom->dir_angle);
	}
	else if (sym == SDLK_s)
	{
		movement.end.x = doom->pos.x - SPEED * cos(doom->dir_angle);
		movement.end.y = doom->pos.y - SPEED * sin(doom->dir_angle);
	}
	return (movement);
}

void	move_player_position(t_doom *doom, int sym)
{
	t_line	movement;

	
	movement.start = doom->pos;
	if (sym == SDLK_w || sym == SDLK_s)
		movement = player_movement(doom, sym, movement);
	else if (sym == SDLK_a || (sym == SDLK_d))
		movement = player_side_movement(doom, sym, movement);
	if (movement_collision(doom, movement) == 0)
		doom->pos = movement.end;
	//update_curr_sector(doom); //send message to update sector
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 18:18:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/06 18:56:52 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	jump_player(t_doom *doom, double dt)
{
	static double	duration = 1;
	double			og_height;

	doom->own_event.jump = 1;
	og_height = PLAYER_HEIGHT + doom->sector[doom->i_sector].height_floor;
	duration += dt;
	doom->player_height += (int)(doom->own_event.velocity * duration);
	doom->own_event.velocity += GRAVITY * duration;
	if (doom->player_height <= og_height)
	{
		doom->own_event.velocity = VELOCITY;
		doom->player_height = og_height;
		doom->own_event.jump = 0;
		duration = 1;
	}
}

int	check_floor_diff(t_doom *doom, int sector, int next_sector)
{
	int		floor_height;
	int		next_floor_height;
	int		floor_diff;

	floor_height = doom->sector[sector].height_floor;
	next_floor_height = doom->sector[next_sector].height_floor;
	floor_diff = next_floor_height - floor_height;
	if (floor_diff < 0)
		doom->own_event.step_down = 1;
	if (floor_diff > 0 && doom->own_event.jump == 0)
		return (-1);
	return (0);
}

int		movement_collision(t_doom *doom, t_line move)
{
	int			x;
	int			height_step;
	t_point		intersect;
	t_sidedef	sidedef;

	x = doom->sector[doom->i_sector].i_sidedefs;
	while (x < doom->sector[doom->i_sector].n_sidedefs\
		+ doom->sector[doom->i_sector].i_sidedefs)
	{
		sidedef = doom->sidedef[x];
		intersect = check_line_intersection(move, sidedef);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			if (sidedef.opp_sector == -1)
				return (-1);
			else if (sidedef.opp_sector != -1)
			{
				height_step = check_floor_diff(doom, doom->i_sector, sidedef.opp_sector);
				if (height_step == -1)
					return (-1);
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

t_point	check_line_intersection(t_line move, t_sidedef sidedef)
{
	t_point	intersect;
	t_point	move_delta;
	t_point sidedef_delta;

	move_delta = line_delta(move.start, move.end);
	sidedef_delta = line_delta(sidedef.line.start, sidedef.line.end);
	intersect = line_intersection(move.start, move_delta,\
	sidedef.line.start, sidedef_delta);
	return (intersect);
}

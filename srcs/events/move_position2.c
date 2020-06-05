/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 18:18:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/05 20:36:05 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	jump_player(t_doom *doom)
{
	int		height;
	int		i;

	height = doom->player_height;
	i = 0;
	while (i < 1 )
	{
		doom->player_height = height + sin(i - PI /180);
		printf("%d\n", doom->player_height);
		doom_render(doom);
		i++;
	}
}

int		movement_collision(t_doom *doom, t_line move)
{
	int			x;
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

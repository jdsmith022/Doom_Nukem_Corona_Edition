/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sector_in_sector.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 23:55:45 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

void			save_current_sector(t_doom *doom, int x, int y)
{
	t_line	sector;
	int		index;

	index = 0;
	while (index < doom->lib.n_sectors)
	{
		sector = g_sc_lines[index];
		if (x > sector.start.x && x < sector.end.x && \
		y > sector.start.y && y < sector.end.y)
		{
			doom->game_design.ed_sprite->sector = index;
			doom->lib.sector[index].n_objects++;
			break ;
		}
		index++;
	}
}

bool			check_sector_in_sector(t_doom *doom, int x, int y)
{
	t_point			intersect;
	t_line			ray;
	int				counter;
	int				index;
	t_sidedef		sidedef;

	counter = 0;
	ray.start.x = x;
	ray.start.y = y;
	ray.end.x = x + doom->cast.max_ray;
	ray.end.y = y;
	index = 0;
	while (index < doom->lib.len_sidedef)
	{
		sidedef = doom->lib.sidedef[index];
		intersect = check_line_intersection(ray, sidedef.line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
			counter++;
		index++;
	}
	if (counter % 2 == 0)
		return (FALSE);
	return (TRUE);
}

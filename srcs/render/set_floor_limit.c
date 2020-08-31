/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_floor_limit.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 22:03:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:34:19 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void		set_floor_limit(t_doom *doom, t_plane *plane, t_sidedef sidedef,
				t_sector *sector)
{
	double	height_floor;
	double	plane_height_std;
	int		plane_bottom;
	int		scale;

	if (doom->i_sector == sector->id)
		sector->floor_end = HEIGHT;
	else
	{
		plane_height_std = doom->cast.texture_height / sidedef.prev_sidedef.distance\
			* doom->cast.dist_to_plane;
		scale = plane->height_standard / doom->cast.texture_height;
		height_floor = sector->height_floor / \
			sidedef.prev_sidedef.distance * doom->cast.dist_to_plane;
		plane_bottom = ((HEIGHT / 2) + (doom->player.height * scale)) - \
			(doom->own_event.y_pitch + height_floor);
		if (plane_bottom <= plane->sidedef_bottom)
			plane_bottom = HEIGHT;
		else if (plane_bottom > HEIGHT)
			plane_bottom = HEIGHT;
		else if (plane_bottom < 0)
			plane_bottom = 0;
		sector->floor_end = plane_bottom;
	}
}

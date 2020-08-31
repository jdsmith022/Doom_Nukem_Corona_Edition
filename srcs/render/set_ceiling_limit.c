/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_ceiling_limit.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 22:03:12 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:42:36 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void		set_ceiling_limit(t_doom *doom, t_sidedef sidedef,
				t_sector *sector)
{
	double		height_ceiling;
	double		plane_height_std;
	int			plane_top;
	int			diff;
	double		scale;

	if (doom->i_sector == sector->id)
		sector->ceiling_end = 0;
	else
	{
		plane_height_std = \
			doom->cast.texture_height / sidedef.prev_sidedef.distance\
			* doom->cast.dist_to_plane;
		scale = plane_height_std / doom->cast.texture_height;
		diff = doom->cast.texture_height - doom->player.height;
		height_ceiling = sector->height_ceiling / \
			sidedef.prev_sidedef.distance * doom->cast.dist_to_plane;
		plane_top = ((HEIGHT / 2) - (diff * scale)) - \
			(doom->own_event.y_pitch + height_ceiling);
		if (plane_top < 0)
			plane_top = 0;
		else if (plane_top > HEIGHT)
			plane_top = HEIGHT;
		sector->ceiling_end = plane_top;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_horizontal_properties.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/10 11:10:57 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/10 11:16:50 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	int			new_height;

	(void)sector;
	new_height = (HEIGHT + doom->player_height) / 2;
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	// height_sidedef = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	height_floor = sector.height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

void    set_properties_horizontal(t_doom *doom, t_sidedef sidedef,
            t_plane *plane, int  x)
{
	set_properties_plane(doom, sidedef, plane, x);
}
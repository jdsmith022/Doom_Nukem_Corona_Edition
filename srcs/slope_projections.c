/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   slope_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/21 14:22:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/11 13:39:03 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		calculate_slope_position(t_doom *doom, t_sidedef sidedef, t_plane *plane)	
{
	(void)doom;
	(void)sidedef;
	(void)plane;
	return (0);
}


int		select_opp_sidedef(t_sector sector)
{
	int		first_sidedef;

	first_sidedef = sector.i_sidedefs;
	if (sector.slope_id == first_sidedef || sector.slope_id == first_sidedef + 1)
		return (sector.slope_id + 2);
	return (sector.slope_id - 2);
}

void		set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	int x, t_plane *plane)
{

	double		height_diff;
	double		floor_dist;
	t_sector	sector;
	int			opp_side;

	x = 0;
	(void)doom;
	(void)sidedef;
	(void)plane;
	sector = doom->sector[doom->i_sector];
	opp_side = select_opp_sidedef(sector);
	if (sidedef.id == sector.slope_id)
		plane->sidedef_bottom = plane->mid_texture_bottom;
	else if (sidedef.id != opp_side)
		plane->sidedef_bottom = calculate_slope_position(doom, sidedef, plane);
	height_diff = (HEIGHT / 2) / (plane->sidedef_bottom - HEIGHT / 2);
	floor_dist = sidedef.distance * height_diff;
	floor_dist = cos(doom->ray_adjacent / (x - FOV / 2));

}
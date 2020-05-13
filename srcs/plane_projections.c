/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/13 17:29:03 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		set_properties_portal(t_doom *doom, t_sidedef sidedef,\
	int opp_sector, t_plane *plane)
{
	double		height_opp_sector;
	int			mid_top;
	int			mid_bottom;

	height_opp_sector = doom->sector[opp_sector].height_ceiling -\
		doom->sector[opp_sector].height_floor;
	height_opp_sector = height_opp_sector / sidedef.distance *\
		doom->dist_to_plane;
	mid_top = (int)(HEIGHT / 2 - height_opp_sector / 2);
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	mid_bottom = (int)(HEIGHT / 2 + height_opp_sector / 2);
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT - 1));
}


void		set_properties_height(t_doom *doom, t_sidedef sidedef,\
	t_sector sector, t_plane *plane)
{
	// double		floor_diff;		
	int			sidedef_top;
	int			sidedef_bottom;	
	// int			ceiling_height;
	// int			sidedef_height;

	//walls
	plane->sidedef_height = doom->wall_height / sidedef.distance * doom->dist_to_plane;
	plane->floor_diff = sector.height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (int)(HEIGHT / 2 - (plane->sidedef_height + plane->floor_diff) / 2);
	plane->sidedef_top = ((sidedef_top >= 0) ? sidedef_top : 0);
	sidedef_bottom = (int)(HEIGHT / 2 + plane->sidedef_height / 2);
	plane->sidedef_bottom = ((sidedef_bottom < HEIGHT) ? sidedef_bottom : (HEIGHT - 1));
	
	//floor and ceiling
	// ceiling_height = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	// sidedef_top = (int)(HEIGHT / 2 - (plane->sidedef_height + ceiling_height) / 2);
	// plane->vertical_top = ((sidedef_top >= 0) ? sidedef_top : 0);


	// int cur_height;
	// double		height_opp_sector;

	// cur_height = sector.height_floor;
	// 	height_opp_sector = doom->sector[sidedef.opp_sector].height_ceiling -\
	// 	doom->sector[sidedef.opp_sector].height_floor;
	// height_opp_sector = height_opp_sector / sidedef.distance *\
	// 	doom->dist_to_plane;
	sidedef_bottom = (int)(HEIGHT / 2 + (plane->sidedef_height - plane->floor_diff) / 2);
	plane->vertical_bottom = ((sidedef_bottom < HEIGHT) ? sidedef_bottom : (HEIGHT - 1));
	// plane->vertical_bottom += plane->floor_diff;
}

void		set_properties_plane(t_doom *doom, t_plane *plane, t_sidedef sidedef, int x)
{
	t_sector	sector;

	sector  = doom->sector[sidedef.sector];
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	ft_bzero(plane, sizeof(plane));
	set_properties_height(doom, sidedef, sector, plane);
	if (sidedef.opp_sector != -1)
		set_properties_portal(doom, sidedef, sidedef.opp_sector, plane);
	if (sector.slope_id != -1)
		set_properties_slope(doom, sidedef, x, plane);
}

void	project_on_plane(t_doom *doom, t_sidedef sidedef, int x, t_point intersect)
{
	t_plane plane;

	set_properties_plane(doom, &plane, sidedef, x);
	plane.intersect = intersect;
	draw_ceiling(doom, x, plane.sidedef_top);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	//draw for floor only of same height, then start draw again for different floor height
	//while you can still see sectors
		//calculate y bottom for sector
		//draw_floor
		//look st next vixible sector
	draw_floor(doom, x, plane);
}

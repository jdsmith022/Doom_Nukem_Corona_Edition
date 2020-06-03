/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/03 12:38:30 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static void		set_properties_portal(t_doom *doom, t_sidedef sidedef,
					int opp_sector, t_plane *plane) //need to sort (if ceiling height changed...floor height changes)
{
	int			new_middle;
	double	height_opp_sector;
	int			mid_top;
	int			mid_bottom;

	new_middle = (HEIGHT + doom->player_height) / 2;
	height_opp_sector = doom->sector[opp_sector].height_ceiling - \
		doom->sector[opp_sector].height_floor;
	height_opp_sector = height_opp_sector / sidedef.distance * \
		doom->dist_to_plane;
	mid_top = (int)(new_middle - height_opp_sector / 2);
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	mid_bottom = (int)(new_middle + height_opp_sector / 2);
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT - 1));
}

static void		set_wall_properties(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	int			new_middle;
	int			sidedef_top;
	int			sidedef_bottom;	

	(void)sector;
	if (sector.height_ceiling != 0)
		new_middle = (HEIGHT + doom->player_height) / 2;
	else
		new_middle = HEIGHT / 2;
	plane->sidedef_height = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (int)(new_middle - plane->sidedef_height / 2);
	plane->sidedef_top = ((sidedef_top >= 0) ? sidedef_top : 0);
	if (sector.height_floor != 0)
		new_middle = (HEIGHT + doom->player_height) / 2;
	sidedef_bottom = (int)(new_middle + plane->sidedef_height / 2);
	plane->sidedef_bottom = ((sidedef_bottom < HEIGHT) ? sidedef_bottom : (HEIGHT - 1));
}

static void 	set_ceiling_properties(t_doom *doom, t_plane *plane,
					t_sidedef sidedef, t_sector sector)
{
	int		new_middle;
	int		ceiling_height;	
	int		ceiling_diff;
	int		ceiling_start;
	int		diff;

	if (sector.height_ceiling != 0)
		new_middle = (HEIGHT + doom->player_height) / 2;
	else
		new_middle = HEIGHT / 2;
	ceiling_height = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	diff = doom->texture_height - sector.height_ceiling;
	ceiling_diff = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	ceiling_start = (int)(new_middle - (ceiling_height - diff) / 2);

	plane->ceiling_start = ((ceiling_start >= 0) ? ceiling_start : 0);
}

static void		set_floor_properties(t_doom *doom, t_plane *plane,
					t_sidedef sidedef, t_sector sector) //floor is not acutally being elevated to where the wall textures starts
{
	int new_middle;
	int	floor_start;
	// int floor_end;
	int	floor_width;
	
	if (sector.height_floor != 0)
		new_middle = (HEIGHT + doom->player_height) / 2;
	else
		new_middle = HEIGHT / 2;
	floor_width = doom->texture_width / sidedef.distance * doom->dist_to_plane;
	doom->height_diff =  sector.height_floor / sidedef.distance * doom->dist_to_plane;
	floor_start = (int)(new_middle + (floor_width - doom->height_diff) / 2);
	plane->floor_start = ((floor_start < HEIGHT) ? floor_start : (HEIGHT - 1));
	// doom->height_diff /= ((sidedef.distance + doom->height_diff) * doom->dist_to_plane);
	// doom->player_height += sector.height_floor;
	// doom->height_diff =  sector.height_floor / sidedef.distance * doom->dist_to_plane;

	// floor_end = (int)(HEIGHT / 2 + ( - ) / 2);;
	// plane->floor_end = ((floor_end > HEIGHT) ? floor_end : (HEIGHT - 1));
}

void		set_properties_plane(t_doom *doom, t_plane *plane,
				t_sidedef sidedef, int x)
{
	t_sector	sector;

	sector  = doom->sector[sidedef.sector];
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	ft_bzero(plane, sizeof(plane));
	set_ceiling_properties(doom, plane, sidedef, sector);
	set_wall_properties(doom, sidedef, sector, plane);
	if (sidedef.opp_sector != -1)
		set_properties_portal(doom, sidedef, sidedef.opp_sector, plane);
	if (sector.slope_id != -1)
		set_properties_slope(doom, sidedef, x, plane);
	set_floor_properties(doom, plane, sidedef, sector);
}

void		project_on_plane(t_doom *doom, t_sidedef sidedef,
				int x, t_point intersect)
{
	t_plane plane;

	set_properties_plane(doom, &plane, sidedef, x);
	plane.intersect = intersect;
	draw_ceiling(doom, x, plane.ceiling_start);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	draw_floor(doom, x, plane, doom->sector[sidedef.sector]) ;
}

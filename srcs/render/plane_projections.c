/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/14 18:40:33 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,\
	int opp_sector, t_plane *plane)
{
	double		height_standard;
	double		height_opp_sector;
	double		height_floor;
	int			mid_top;
	int			mid_bottom;

	height_standard = doom->wall_height_std /\
		sidedef.distance * doom->dist_to_plane;
	height_opp_sector = doom->lib.sector[opp_sector].height_ceiling /\
		sidedef.distance * doom->dist_to_plane;
	height_floor = doom->lib.sector[opp_sector].height_floor /\
		sidedef.distance * doom->dist_to_plane;
	mid_top = (int)((HEIGHT / 2 + doom->player_height)\
		- (height_standard / 2) - (height_standard - height_opp_sector) - doom->own_event.y_pitch);
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	mid_bottom = (int)((HEIGHT / 2 + doom->player_height)\
		+ (height_standard / 2) - height_floor - doom->own_event.y_pitch);
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ?\
		mid_bottom : (HEIGHT - 1));
}

void	set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,\
	t_sector sector, t_plane *plane)
{
	double		height_sidedef;
	double		height_standard;
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;

	height_standard = doom->wall_height_std /\
		sidedef.distance * doom->dist_to_plane;
	height_sidedef = sector.height_ceiling /\
		sidedef.distance * doom->dist_to_plane;
	height_floor = sector.height_floor /\
		sidedef.distance * doom->dist_to_plane;
	sidedef_top = (int)((HEIGHT / 2 + doom->player_height) -\
		(height_standard / 2) - (height_standard -height_sidedef) - doom->own_event.y_pitch);
	plane->sidedef_top = ((sidedef_top >= 0) ? sidedef_top : 0);
	sidedef_bottom = (int)((HEIGHT / 2 + doom->player_height)\
		+ (height_standard / 2) - height_floor - doom->own_event.y_pitch);
	plane->sidedef_bottom = ((sidedef_bottom < HEIGHT ?\
		sidedef_bottom : (HEIGHT - 1)));
	if (sidedef.opp_sector != -1)
		set_properties_plane_portal(doom, sidedef, sidedef.opp_sector, plane);
}

t_plane	set_properties_plane(t_doom *doom, t_sidedef sidedef,\
	t_point intersect, int x)
{
	t_plane		plane;
	t_sector	sector;

	sector = doom->lib.sector[sidedef.sector];
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	ft_bzero(&plane, sizeof(plane));
	plane.intersect = intersect;
	set_properties_plane_sidedef(doom, sidedef, sector, &plane);
	return (plane);
}

void	project_on_plane(t_doom *doom, t_sidedef sidedef,\
	int x, t_point intersect)
{
	t_plane		plane;

	plane = set_properties_plane(doom, sidedef, intersect, x);
	draw_ceiling(doom, x, plane.sidedef_top);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	draw_floor(doom, x, plane.sidedef_bottom);
}

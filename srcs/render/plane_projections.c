/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/03 18:17:10 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/03 12:59:00 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

// static void		set_properties_portal(t_doom *doom, t_sidedef sidedef,
// 					int opp_sector, t_plane *plane)
// {
// 	int			new_middle;
// 	double	height_opp_sector;
// 	int			mid_top;
// 	int			mid_bottom;

// 	new_middle = (HEIGHT + doom->player_height) / 2;
// 	height_opp_sector = doom->lib.sector[opp_sector].height_ceiling - \
// 		doom->lib.sector[opp_sector].height_floor;
// 	height_opp_sector = height_opp_sector / sidedef.distance * \
// 		doom->dist_to_plane;
// 	mid_top = (int)(new_middle - height_opp_sector / 2);
// 	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
// 	mid_bottom = (int)(new_middle + height_opp_sector / 2);
// 	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT -1));
// }

// static void		set_wall_properties(t_doom *doom, t_sidedef sidedef,
// 					t_sector sector, t_plane *plane)
// {
// 	int			new_middle;
// 	int			sidedef_top;
// 	int			sidedef_bottom;

// 	(void)sector;
// 	new_middle = HEIGHT / 2;
// 	plane->sidedef_height = 64 / sidedef.distance * doom->dist_to_plane;
// 	sidedef_top = (int)(new_middle - plane->sidedef_height / 2);
// 	plane->sidedef_top = ((sidedef_top >= 0) ? sidedef_top : 0);
// 	sidedef_bottom = (int)(new_middle + plane->sidedef_height / 2);
// 	plane->sidedef_bottom = ((sidedef_bottom < HEIGHT) ? sidedef_bottom : (HEIGHT));
// }

// static void 	set_ceiling_properties(t_doom *doom, t_plane *plane,
// 					t_sidedef sidedef, t_sector sector)
// {
// 	int		new_middle;
// 	int		ceiling_height;
// 	int		ceiling_diff;
// 	int		ceiling_start;
// 	int		diff;

// 	new_middle = HEIGHT / 2;
// 	ceiling_height = doom->texture_width / sidedef.distance * doom->dist_to_plane;
// 	diff = 64 - sector.height_ceiling;
// 	ceiling_diff = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
// 	ceiling_start = (int)(new_middle - (ceiling_height - diff) / 2);

// 	plane->ceiling_start = ((ceiling_start >= 0) ? ceiling_start : 0);
// }

// static void		set_floor_properties(t_doom *doom, t_plane *plane,
// 					t_sidedef sidedef, t_sector sector)
// {
// 	int new_middle;
// 	int	floor_start;
// 	int	floor_width;
// 	double height_diff;

// 	new_middle = HEIGHT / 2;
// 	floor_width = doom->texture_width / sidedef.distance * doom->dist_to_plane;
// 	height_diff =  sector.height_floor / sidedef.distance * doom->dist_to_plane;
// 	floor_start = (int)(new_middle + (floor_width - height_diff) / 2);
// 	plane->floor_start = ((floor_start < HEIGHT) ? floor_start : (HEIGHT));
// }

// void		set_properties_plane(t_doom *doom, t_plane *plane,
// 				t_sidedef sidedef, int x)
// {
// 	t_sector	sector;

// 	sector  = doom->lib.sector[sidedef.sector];
// 	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
// 	ft_bzero(plane, sizeof(plane));
// 	set_ceiling_properties(doom, plane, sidedef, sector);
// 	set_wall_properties(doom, sidedef, sector, plane);
// 	if (sidedef.opp_sector != -1)
// 		set_properties_portal(doom, sidedef, sidedef.opp_sector, plane);
// 	// if (sector.slope_id != -1)
// 	// 	set_properties_slope(doom, sidedef, x, plane);
// 	set_floor_properties(doom, plane, sidedef, sector);
// }

// void		project_on_plane(t_doom *doom, t_sidedef sidedef,
// 				int x, t_point intersect)
// {
// 	t_plane plane;

// 	set_properties_plane(doom, &plane, sidedef, x);
// 	plane.intersect = intersect;
// 	draw_ceiling(doom, x, plane.sidedef_top);
// 	if (sidedef.opp_sector == -1)
// 		draw_onesided_sidedef(doom, plane, sidedef, x);
// 	else
// 		draw_portal_sidedef(doom, plane, sidedef, x);
// 	printf("here\n");
// 	draw_texture_floor(doom, x, plane.floor_start);
// }

// static void 	set_ceiling_properties(t_doom *doom, t_plane *plane,
// 					t_sidedef sidedef, t_sector sector)
// {
// 	int		new_middle;
// 	int		ceiling_height;
// 	int		ceiling_diff;
// 	int		ceiling_start;
// 	int		diff;

// 	new_middle = HEIGHT / 2;
// 	ceiling_height = doom->texture_height_std / sidedef.distance * doom->dist_to_plane;
// 	diff = doom->texture_height_std - sector.height_ceiling;
// 	ceiling_diff = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
// 	ceiling_start = (int)(new_middle - (ceiling_height - diff) / 2);

// 	plane->ceiling_start = ((ceiling_start >= 0) ? ceiling_start : 0);
// }

// static void		set_floor_properties(t_doom *doom, t_plane *plane,
// 					t_sidedef sidedef, t_sector sector)
// {
// 	int new_middle;
// 	int	floor_start;
// 	int	floor_width;
// 	int height_diff;

// 	new_middle = HEIGHT / 2;
// 	floor_width = 64 / sidedef.distance * doom->dist_to_plane;
// 	height_diff =  sector.height_floor / sidedef.distance * doom->dist_to_plane;
// 	floor_start = (int)(new_middle + (floor_width - height_diff) / 2);
// 	plane->floor_start = ((floor_start < HEIGHT) ? floor_start : (HEIGHT - 1));
// }

static void		wall_offset(t_plane *plane, int sidedef_top)
{
	plane->wall_offset = 0;
	if (sidedef_top < 0)
	{
		plane->wall_offset = abs(sidedef_top);
		plane->sidedef_top = 0;
	}
	else
		plane->sidedef_top = sidedef_top;
}

static void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					int opp_sector, t_plane *plane)
{
	double		height_opp_sector;
	double		height_floor;
	int			mid_top;
	int			mid_bottom;
	int			div_height_std;

	div_height_std = plane->height_standard / 2;
	height_opp_sector = doom->lib.sector[opp_sector].height_ceiling / sidedef.distance * doom->dist_to_plane;
	height_floor = doom->lib.sector[opp_sector].height_floor / sidedef.distance * doom->dist_to_plane;

	mid_top = ((HEIGHT + doom->player_height) / 2 - div_height_std); //- (plane->height_standard - height_opp_sector) - doom->own_event.y_pitch);
	plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	mid_bottom = ((HEIGHT + doom->player_height) / 2 + div_height_std);// - height_floor - doom->own_event.y_pitch);
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ?\
		mid_bottom : (HEIGHT));
}

static void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	// double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	int			new_height;

	(void)sector;
	new_height = HEIGHT / 2;
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	// height_sidedef = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
	// height_floor = sector.height_floor / sidedef.distance * doom->dist_to_plane;
	sidedef_top = (new_height - div_height_std) - doom->own_event.y_pitch;;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (new_height + div_height_std) - doom->own_event.y_pitch;;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

static void		set_properties_plane(t_doom *doom, t_sidedef sidedef,\
					t_plane *plane, int x)
{
	t_sector	sector;

	ft_bzero(plane, sizeof(plane));
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sector = doom->lib.sector[sidedef.sector];
	set_properties_plane_sidedef(doom, sidedef, sector, plane);
	if (sidedef.opp_sector != -1)
		set_properties_plane_portal(doom, sidedef,\
			sidedef.opp_sector, plane);
}

void		project_on_plane(t_doom *doom, t_sidedef sidedef,
				int x, t_point intersect)
{
	t_plane		plane;

	set_properties_plane(doom, sidedef, &plane, x);
	plane.intersect = intersect;
	// if (doom->lib.sector[sidedef.sector].height_ceiling == 0)
	// 	draw_texture_ceiling(doom, x, plane.sidedef_top);
	// else
		draw_ceiling(doom, x, plane.sidedef_top);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	// if (doom->lib.sector[sidedef.sector].height_floor == 0)
	// {
		// set_floor_properties(doom, &plane, sidedef, doom->lib.sector[sidedef.sector]);
		draw_texture_floor(doom, x, plane.floor_start);
	// }
	// else
		// draw_floor(doom, x, plane.sidedef_bottom);
}

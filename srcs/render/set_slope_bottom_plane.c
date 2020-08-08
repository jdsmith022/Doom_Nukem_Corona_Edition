#include "../../includes/doom.h"

static int		set_bottom_plane(t_doom *doom, t_sidedef sidedef,\
					t_sector sector)
{
	int		bottom;
	double	height_floor;
	int		new_height;
	int		plane_bottom;
	double	plane_height_std;

	new_height = (HEIGHT / 2) + doom->player_height;
	plane_height_std = doom->texture_height / sidedef.prev_sidedef.distance\
		* doom->dist_to_plane;
	plane_height_std = plane_height_std / 2 + sector.height_ceiling;
	height_floor = (sector.height_floor + sector.slope.bottom_height)\
		/ sidedef.prev_sidedef.distance * doom->dist_to_plane;
	plane_bottom = (new_height + plane_height_std)\
		- doom->own_event.y_pitch - height_floor;
	plane_bottom = ((plane_bottom < HEIGHT ? plane_bottom : (HEIGHT)));
	return (plane_bottom);
}

static void		set_sector_plane(t_doom *doom, double distance,\
					t_sidedef sidedef, t_sector *sector)
{
	sector->slope.bottom_height = tan(sector->slope_floor) * distance;
	sector->slope.bottom_plane = set_bottom_plane(doom, sidedef,\
		*sector);
	sector->slope.prev_intersect = sidedef.prev_sidedef.intersect;
	sector->slope.dist_to_bottom =\
		fabs(points_distance(sidedef.prev_sidedef.intersect,\
		sector->slope.intersect));
}

static double	find_point_distance(t_doom *doom, t_sidedef bottom_line,
					t_sector *sector, t_sidedef sidedef)
{
	t_point		conn_point;
	double		distance;
	int			opp_side;

	if (bottom_line.id == sector->slope_floor_id)
		distance = 0;
	opp_side = get_opp_side_of_slope(*sector, sector->slope_floor_id);
	if (bottom_line.id == opp_side)
	{
		distance = fabs(point_line_distance(bottom_line.line.start,\
			doom->lib.sidedef[sector->slope_floor_id].line));
	}
	else if (bottom_line.id != sector->slope_floor_id &&
	bottom_line.id != opp_side)
	{
		conn_point = get_connecting_point(bottom_line.line,\
			doom->lib.sidedef[sector->slope_floor_id].line);
		distance = points_distance(conn_point, sidedef.prev_sidedef.intersect);
	}
	return (distance);
}

void			set_slope_bottom_values(t_doom *doom, t_sidedef sidedef,\
					t_sector *sector)
{
	t_sidedef	bottom_line;
	double		distance;
	t_sector	opp_sector;

	bottom_line = doom->lib.sidedef[sidedef.prev_sidedef.id];
	opp_sector = doom->lib.sector[sidedef.sector];
	if (opp_sector.slope_floor_id == -1)
		sector->slope.prev_floor_id = -1;
	bottom_line = get_other_side_of_line(doom, bottom_line, *sector);
	distance = find_point_distance(doom, bottom_line, sector, sidedef);
	set_sector_plane(doom, distance, sidedef, sector);
}

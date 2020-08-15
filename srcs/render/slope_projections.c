#include "../../includes/doom.h"

static void		find_line_connections(t_doom *doom, t_sector *sector,
					t_slope *slope, t_sidedef sidedef)
{
	slope->opp_side = get_opp_side_of_slope(*sector, sector->slope_floor_id);
	if (sidedef.id == slope->opp_side)
	{
		slope->distance = fabs(point_line_distance(sidedef.line.end,\
			doom->lib.sidedef[sector->slope_floor_id].line));
	}
	if (sidedef.id != sector->slope_floor_id && sidedef.id != slope->opp_side)
	{
		slope->conn_point = get_connecting_point(sidedef.line,\
		doom->lib.sidedef[sector->slope_floor_id].line);
		slope->distance = points_distance(sidedef.intersect, slope->conn_point);
	}
}

t_slope			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_sector *sector)
{
	t_slope		slope;

	slope.distance = 0;
	slope.intersect = sidedef.intersect;
	slope.sidedef_id = sidedef.id;
	if (sidedef.sector != sector->id)
		sidedef = get_other_side_of_line(doom, sidedef, *sector);
	if (sidedef.id == sector->slope_floor_id)
	{
		slope.height = 0;
		return (slope);
	}
	find_line_connections(doom, sector, &slope, sidedef);
	slope.distance *= cos(doom->ray_adjacent * sidedef.intersect.x - FOV / 2);
	slope.height = tan(sector->slope_floor) * slope.distance;
	return (slope);
}

void		slope_plane_settings(t_doom *doom, t_sidedef sidedef,
					t_sector *sector)
{
	sector->slope = set_properties_slope(doom, sidedef, sector);
	sector->height_floor += sector->slope.height;
}

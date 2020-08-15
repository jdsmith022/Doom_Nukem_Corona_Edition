#include "../../includes/doom.h"

static double		update_cam_height(t_doom *doom, t_sidedef sidedef,\
					t_sector *sector)
{
	double		distance;
	t_line		slope;
	double		slope_height;

	slope = doom->lib.sidedef[sector->slope_floor_id].line;
	distance = fabs(point_line_distance(doom->pos, slope));
	slope_height = tan(sector->slope_floor) * distance;
	printf("%f\n", slope_height);
	return (slope_height);
}

double			set_slope_delta(t_doom *doom, t_sector *sector, int y)
{
	double		plane_distance;
	double		delta_slope;
	double		delta_height;
	double		delta_distance;

	delta_height = sector->slope.height - sector->slope.bottom_height;
	plane_distance = y - sector->slope.bottom_plane;
	delta_slope = delta_height / plane_distance;
	delta_distance = sector->slope.dist_to_bottom / plane_distance;
	delta_distance *= cos(doom->ray_adjacent * sector->plane_x - FOV / 2);
	sector->slope.prev_floor_id = sector->slope.sidedef_id;
	return (delta_distance);
}

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
					t_sector *sector, int flag)
{
	if (flag == 1 && sector->slope_floor_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		sector->height_floor += sector->slope.height;
	}
	if (flag == 0 && sector->slope_floor_id != -1)
	{
		sector->slope = set_properties_slope(doom, sidedef, sector);
		if (doom->i_sector != sector->id)
			set_slope_bottom_values(doom, sidedef, sector);
		sector->height_floor += sector->slope.height;
	}
	//if (doom->i_sector == sector->id)
	//	doom->cam_slope_height = 0; //update_cam_height(doom, sidedef, sector);
	//else
	//	doom->cam_slope_height = 0;
}

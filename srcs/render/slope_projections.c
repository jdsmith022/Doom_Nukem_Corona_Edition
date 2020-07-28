#include "../../includes/doom.h"

t_sidedef	get_other_side_of_line(t_doom *doom, t_sidedef sidedef, t_sector sector)
{
	t_point		start;
	t_point		end;
	t_point		opp_start;
	t_point		opp_end;
	size_t		i;

	start = sidedef.line.start;
	end = sidedef.line.end;
	i = sector.i_sidedefs;
	while (i < sector.i_sidedefs + sector.n_sidedefs)
	{
		opp_start = doom->lib.sidedef[i].line.start;
		opp_end = doom->lib.sidedef[i].line.end;
		if (((start.x == opp_start.x && start.y == opp_start.y) &&\
			(end.x == opp_end.x && end.y == opp_end.y)) ||\
			((start.x == opp_end.x && start.y == opp_end.y) &&\
			(end.x == opp_start.x && end.y == opp_start.y)))
		{
			doom->lib.sidedef[i].intersect = sidedef.intersect;
			return (doom->lib.sidedef[i]);
		}
		i++;
	}
	return (doom->lib.sidedef[i]);
}

int			get_opp_side_of_slope(t_sector sector)
{
	int		sidedef_index;

	sidedef_index = sector.i_sidedefs;
	if (sector.slope_id == sidedef_index ||\
		sector.slope_id == sidedef_index + 1)
		return (sector.slope_id + 2);
	return (sector.slope_id - 2);
}

t_point		get_connecting_point(t_line sidedef, t_line conn_sidedef)
{
	t_point		start;
	t_point		end;
	t_point		conn_start;
	t_point		conn_end;

	start = sidedef.start;
	end = sidedef.end;
	conn_start = conn_sidedef.start;
	conn_end = conn_sidedef.end;
	if ((start.x == conn_start.x && start.y == conn_start.y) ||
		(start.x == conn_end.x && start.y == conn_end.y))
		return (start);
	return (end);
}

double			set_slope_delta(t_doom *doom, t_sector *sector, int y)
{
	double		height_diff;
	double		distance;
	double		height;
	double		delta_height;
	double		delta_steps;

	height_diff = sector->slope.bottom_height - sector->slope.height;
	delta_steps = sector->slope.bottom_plane - y;
	delta_height = height_diff / delta_steps;
	sector->slope.prev_id = sector->slope.sidedef_id;
	return (delta_height);
}

int			set_bottom_plane(t_doom *doom, t_sidedef sidedef,\
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

void		set_slope_bottom_values(t_doom *doom, t_sidedef sidedef,\
				t_sector *sector)
{
	t_sidedef	bottom_line;
	int			opp_side;
	double		distance;
	t_point		conn_point;

	bottom_line = doom->lib.sidedef[sidedef.prev_sidedef.id];
	bottom_line = get_other_side_of_line(doom, bottom_line, *sector);
	if (bottom_line.id == sector->slope_id)
		distance = 0;
	opp_side = get_opp_side_of_slope(*sector);
	if (bottom_line.id == opp_side)
		distance = fabs(point_line_distance(bottom_line.line.start,\
			doom->lib.sidedef[sector->slope_id].line));
	else if (bottom_line.id != sector->slope_id && sidedef.id != opp_side)
	{
		conn_point = get_connecting_point(bottom_line.line,\
			doom->lib.sidedef[sector->slope_id].line);
		distance = points_distance(conn_point, sidedef.prev_sidedef.intersect);
	}
	sector->slope.bottom_height = tan(sector->slope_floor) * distance;
	sector->slope.bottom_plane = set_bottom_plane(doom, sidedef,\
		*sector);
	sector->slope.dist_to_bottom = fabs(points_distance(sidedef.intersect,\
		sector->slope.intersect));
}

t_slope			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_sector *sector)
{
	t_slope		slope;

	slope.distance = 0;
	if (sidedef.sector != sector->id)
		sidedef = get_other_side_of_line(doom, sidedef, *sector);
	if (sidedef.id == sector->slope_id)
	{
		slope.height = 0;
		return (slope);
	}
	slope.opp_side = get_opp_side_of_slope(*sector);
	if (sidedef.id == slope.opp_side)
		slope.distance = fabs(point_line_distance(sidedef.line.end,\
			doom->lib.sidedef[sector->slope_id].line));
	if (sidedef.id != sector->slope_id && sidedef.id != slope.opp_side)
	{
		slope.conn_point = get_connecting_point(sidedef.line,\
		doom->lib.sidedef[sector->slope_id].line);
		slope.distance = points_distance(sidedef.intersect, slope.conn_point);
	}
	slope.height = tan(sector->slope_floor) * slope.distance;
	slope.intersect = sidedef.intersect;
	slope.sidedef_id = sidedef.id;
	return (slope);
}


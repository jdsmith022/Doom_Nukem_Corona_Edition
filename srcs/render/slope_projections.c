#include "../../includes/doom.h"

t_sidedef	get_other_side(t_doom *doom, t_sidedef sidedef, t_sector sector)
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

int			get_opp_sidedef(t_sector sector)
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

int			set_bottom_plane(t_doom *doom, t_sidedef sidedef,\
				t_sector sector, int height_standard)
{
	int		bottom;
	double	height_floor;
	int		new_height;
	int		plane_bottom;
	int		div_height_std;

	height_floor = (sector.height_floor + sector.slope.height)\
		/ sidedef.distance * doom->dist_to_plane;
	new_height = (HEIGHT / 2) + doom->player_height;
	div_height_std = height_standard / 2;
	plane_bottom = (new_height + div_height_std)\
		- doom->own_event.y_pitch - height_floor;
	return (plane_bottom);
}

int			set_slope_bottom_values(t_doom *doom, t_prev_sidedef sidedef,\
				t_sector sector, int plane_height_std)
{
	t_sidedef	bottom_sidedef;
	int			opp_side;
	double		distance;
	t_point		conn_point;

	bottom_sidedef = doom->lib.sidedef[sidedef.id];
	bottom_sidedef = get_other_side(doom, bottom_sidedef, sector);
	if (bottom_sidedef.id == sector.slope_id)
		distance = 0;
	opp_side = get_opp_sidedef(sector);
	if (bottom_sidedef.id == opp_side)
		distance = fabs(point_line_distance(bottom_sidedef.line.start,\
			doom->lib.sidedef[sector.slope_id].line));
	else if (bottom_sidedef.id != sector.slope_id && sidedef.id != opp_side)
	{
		conn_point = get_connecting_point(bottom_sidedef.line,\
			doom->lib.sidedef[sector.slope_id].line);
		distance = points_distance(conn_point, sidedef.intersect);
	}
	sector.slope.height = tan(sector.slope_floor) * distance;
	return (set_bottom_plane(doom, bottom_sidedef, sector, plane_height_std));
}

t_slope			set_properties_slope(t_doom *doom, t_sidedef sidedef,\
	t_sector *sector)
{
	t_slope		slope;

	slope.distance = 0;
	if (sidedef.sector != sector->id)
		sidedef = get_other_side(doom, sidedef, *sector);
	if (sidedef.id == sector->slope_id)
	{
		slope.height = 0;
		return (slope);
	}
	slope.opp_side = get_opp_sidedef(*sector);
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


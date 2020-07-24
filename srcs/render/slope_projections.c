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

int			get_opp_sidedef(t_sector sector)
{
	int			sidedef_index;

	sidedef_index = sector.i_sidedefs;
	if (sector.slope_id == sidedef_index ||\
		sector.slope_id == sidedef_index + 1)
		return (sector.slope_id + 2);
	return (sector.slope_id - 2);
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
	slope.conn_point = get_connecting_point(sidedef.line,\
		doom->lib.sidedef[sector->slope_id].line);
	if (sidedef.id != sector->slope_id && sidedef.id != slope.opp_side)
		slope.distance = points_distance(sidedef.intersect, slope.conn_point);
	if (sidedef.id == slope.opp_side)
		slope.distance = fabs(point_line_distance(sidedef.line.end,\
			doom->lib.sidedef[sector->slope_id].line));
	slope.height = tan(sector->slope_floor) * slope.distance;
	slope.intersect = sidedef.intersect;
	slope.sidedef_id = sidedef.id;
	printf("%f\n", slope.height);
	return (slope);
}


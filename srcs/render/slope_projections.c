#include "../../includes/doom.h"

static int		get_other_side_of_line(t_doom *doom,\
					t_sidedef sidedef, t_sector sector)
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
			return (doom->lib.sidedef[i].id);
		}
		i++;
	}
	return (doom->lib.sidedef[i].id);
}

double		set_slope_height(t_doom *doom, t_sidedef sidedef,\
	t_sector sector)
{
	double	height;
	double	distance;

	if (sidedef.sector != sector.id)
		sidedef.id = get_other_side_of_line(doom, sidedef, sector);
	if (sidedef.id == sector.slope_floor_id)
		height = 0;
	else
	{
		distance = fabs(point_line_distance(sidedef.intersect,\
			doom->lib.sidedef[sector.slope_floor_id].line));
		height = tan(sector.slope_floor) * distance;
	}
	if (sidedef.id != sector.slope_floor_id)
		printf("id = %d, height = %f\n", sidedef.id, height);
	return (height);
}

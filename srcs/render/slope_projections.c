#include "../../includes/doom.h"

double		set_slope_height(t_doom *doom, t_sidedef sidedef,\
	t_sector sector)
{
	double	height;
	double	distance;

	if (sidedef.id == sector.slope_floor_id)
		height = 0;
	else
	{
		distance = fabs(point_line_distance(sidedef.intersect,\
			doom->lib.sidedef[sector.slope_floor_id].line));
		height = tan(sector.slope_floor) * distance;
	}
	//printf("height %f\n");
	return (height);
}
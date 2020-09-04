#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

bool		check_sector_in_sector(t_doom *doom, t_point pos)
{
	t_ray			ray;
	int				counter;
	t_point			intersect;
	t_ed_sidedef	*sidedef;
	t_point			distance;

	counter = 0;
	sidedef = doom->game_design.sd_head->next;
	ray.line.start = pos;
	ray.line.end.x = pos.x + doom->cast.max_ray;
	ray.line.end.y = pos.y;
	distance.y = INFINITY;
	while (sidedef != NULL)
	{
		intersect = check_line_intersection(ray.line, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			counter++;
			distance.x = point_distance(intersect, pos);
			if (distance.x < distance.y)
			{
				doom->game_design.pl_sec = sidedef->sector;
				distance.y = distance.x;
			}
		}
		sidedef = sidedef->next;
	}
	if (counter % 2 != 0)
		return (TRUE);
	return (FALSE);
}

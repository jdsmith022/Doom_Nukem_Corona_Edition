#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

bool		check_sector_in_sector(t_doom *doom, t_point pos)
{
	t_ray			ray;
	int				counter;
	t_point			intersect;
	t_ed_sidedef	*sidedef;

	counter = 0;
	sidedef = doom->game_design.sd_head->next;
	ray.line.start = pos;
	ray.line.end.x = pos.x + doom->cast.max_ray;
	ray.line.end.y = pos.y;
	while (sidedef != NULL)
	{
		intersect = check_line_intersection(ray.line, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			counter++;
			if (doom->game_design.pl_pos == TRUE && counter == 1)
				doom->game_design.pl_sec = sidedef->sector;
		}
		sidedef = sidedef->next;
	}
	if (counter % 2 != 0)
		return (TRUE);
	return (FALSE);
}

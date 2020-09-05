#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		check_min_distance(t_doom *doom, t_point *distance,
					t_point intersect, t_ed_sidedef *sidedef)
{
	if (distance->x < distance->y)
	{
		doom->game_design.cur_sector = sidedef->sector;
		printf("current sector = %d\n", doom->game_design.cur_sector);
		distance->y = distance->x;
	}
}

static void		set_ray(t_doom *doom, t_ray *ray, t_point pos)
{
	ray->line.start = pos;
	ray->line.end.x = pos.x + doom->cast.max_ray;
	ray->line.end.y = pos.y;
}

bool			check_sector_in_sector(t_doom *doom, t_point pos)
{
	t_point			intersect;
	t_ray			ray;
	int				counter;
	t_ed_sidedef	*sidedef;
	t_point			distance;

	counter = 0;
	sidedef = doom->game_design.sd_head->next;
	set_ray(doom, &ray, pos);
	distance.y = INFINITY;
	while (sidedef != NULL)
	{
		intersect = check_line_intersection(ray.line, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			counter++;
			distance.x = point_distance(intersect, pos);
			check_min_distance(doom, &distance, intersect, sidedef);
		}
		sidedef = sidedef->next;
	}
	if (counter % 2 != 0)
		return (TRUE);
	return (FALSE);
}

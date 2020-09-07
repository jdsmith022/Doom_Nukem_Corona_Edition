#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

static bool		save_current_sector(t_doom *doom, t_point pos,
					t_point intersect, t_ed_sidedef *sidedef)
{
	static double	prev_distance = INFINITY;
	double			distance;
	t_line			ray;

	distance = point_distance(intersect, pos);
	if (distance <= prev_distance)
	{
		if (sidedef->opp_sector == -1)
		{
			doom->game_design.cur_sector = sidedef->sector;
			return (TRUE);
		}	
		prev_distance = distance;
	}
	return (FALSE);
}

static t_line		set_ray(t_doom *doom, t_line ray, int x)
{
	double 		angle;

	angle = clamp_angle(angle + (30 * (PI / 180)));
	ray.end.x = ray.start.x + doom->cast.max_ray * cos(angle);
	ray.end.y = ray.start.y + doom->cast.max_ray * sin(angle);
	ray.end.x = ray.end.x < 0 ? 0 : ray.end.x;
	ray.end.y = ray.end.y < 0 ? 0 : ray.end.y;
	printf("set new ray\n");
	return (ray);
}

bool			check_sector_in_sector(t_doom *doom, t_line ray, int x)
{
	t_point			intersect;
	int				counter;
	t_ed_sidedef	*sidedef;
	int				sector;
	

	counter = 0;
	sidedef = doom->game_design.sd_head->next;
	while (sidedef != NULL)
	{
		if (doom->game_design.edit_sector ==  FALSE &&\
			sidedef->id == doom->game_design.ed_sidedef->id)
			break ;
		intersect = check_line_intersection(ray, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			counter++;
			sector = save_current_sector(doom, intersect, ray.start, sidedef);
		}
		sidedef = sidedef->next;
		printf("ray = %f, %f - %f, %f\n", ray.start.x, ray.start.y, ray.end.x, ray.end.y);
	}
	if (counter % 2 == 0)
		return (FALSE);
	else if (sector != TRUE)
		check_sector_in_sector(doom, set_ray(doom, ray, x + 10));
	return (TRUE);
}

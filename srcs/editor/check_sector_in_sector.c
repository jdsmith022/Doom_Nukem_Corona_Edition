#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

static bool		get_current_sector(t_doom *doom, t_line dist_to_sd,
					t_ed_sidedef *sidedef, double *prev_distance)
{
	double			distance;
	t_line			ray;

	distance = point_distance(dist_to_sd.start, dist_to_sd.end);
	if (distance < *prev_distance)
	{
		if (sidedef->opp_sector == -1)
		{
			doom->game_design.cur_sector = sidedef->sector;
			printf("checkout = %d\n", doom->game_design.cur_sector);
			return (TRUE);
		}
		*prev_distance = distance;
	}
	return (FALSE);
}

t_line			set_ray(t_doom *doom, t_line ray)
{
	static double 	angle;

	angle = clamp_angle(angle + (30 * (PI / 180)));
	ray.end.x = ray.start.x + doom->cast.max_ray * cos(angle);
	ray.end.y = ray.start.y + doom->cast.max_ray * sin(angle);
	ray.end.x = ray.end.x < 0 ? 0 : ray.end.x;
	ray.end.y = ray.end.y < 0 ? 0 : ray.end.y;
	return (ray);
}

void 			save_current_sector(t_doom *doom, t_line ray)
{
	t_ed_sidedef 	*sidedef;
	t_point 		intersect;
	t_line			line;
	bool 			valid_sector;
	double			distance;

	sidedef = doom->game_design.sd_head->next;
	distance = INFINITY;
	while (sidedef != NULL)
	{
		intersect = check_line_intersection(ray, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			line.start = ray.start;
			line.end = intersect;
			valid_sector = get_current_sector(doom, line,\
				sidedef, &distance);
			if (valid_sector == FALSE)
			{
				distance = INFINITY;
				save_current_sector(doom, set_ray(doom, ray));
			}
		}
		sidedef = sidedef->next;
	}
}

bool			check_sector_in_sector(t_doom *doom, t_line ray)
{
	t_point			intersect;
	int				counter;
	t_ed_sidedef	*sidedef;
	bool			sector;

	counter = 0;
	sidedef = doom->game_design.sd_head->next;
	while (sidedef != NULL)
	{
		if (doom->game_design.edit_sector ==  FALSE &&\
			sidedef->id == doom->game_design.ed_sidedef->id)
			break ;
		intersect = check_line_intersection(ray, sidedef->line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
			counter++;
		sidedef = sidedef->next;
	}
	if (counter % 2 == 0)
		return (FALSE);
	return (TRUE);
}

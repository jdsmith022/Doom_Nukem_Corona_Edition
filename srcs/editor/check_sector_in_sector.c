/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_sector_in_sector.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 14:09:04 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

static bool		get_current_sector(t_doom *doom, t_line dist_to_sd,
					t_sidedef sidedef, double *prev_distance)
{
	double			distance;
	t_line			ray;

	distance = point_distance(dist_to_sd.start, dist_to_sd.end);
	if (distance < *prev_distance)
	{
		if (sidedef.opp_sector == -1)
		{
			doom->game_design.i_sector = sidedef.sector;
			return (TRUE);
		}
		*prev_distance = distance;
	}
	return (FALSE);
}

t_line			set_ray(t_doom *doom, t_line ray)
{
	static double	angle;

	angle = clamp_angle(angle + (30 * (PI / 180)));
	ray.end.x = ray.start.x + doom->cast.max_ray * cos(angle);
	ray.end.y = ray.start.y + doom->cast.max_ray * sin(angle);
	ray.end.x = ray.end.x < 0 ? 0 : ray.end.x;
	ray.end.y = ray.end.y < 0 ? 0 : ray.end.y;
	return (ray);
}

static void		reset_ray(t_doom *doom, double *distance, t_line *ray)
{
	*distance = INFINITY;
	*ray = set_ray(doom, *ray);
}

void			save_current_sector(t_doom *doom, t_line ray)
{
	t_point			intersect;
	t_line			line;
	int				index;
	bool			valid_sector;
	double			distance;

	distance = INFINITY;
	index = 0;
	while (index < doom->lib.len_sidedef)
	{
		intersect = check_line_intersection(ray, \
			doom->lib.sidedef[index].line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
		{
			line.start = ray.start;
			line.end = intersect;
			valid_sector = get_current_sector(doom, line,\
				doom->lib.sidedef[index], &distance);
		}
		index++;
		if (valid_sector == FALSE && index == doom->lib.len_sidedef)
		{
			reset_ray(doom, &distance, &ray);
			index = 0;
		}
	}
}

bool			check_sector_in_sector(t_doom *doom, t_line ray)
{
	t_point			intersect;
	int				counter;
	int				index;
	t_sidedef		sidedef;
	bool			sector;

	counter = 0;
	while (index < doom->lib.len_sidedef)
	{
		sidedef = doom->lib.sidedef[index];
		intersect = check_line_intersection(ray, sidedef.line);
		if (isnan(intersect.x) == 0 && isnan(intersect.y) == 0)
			counter++;
		index++;
	}
	if (counter % 2 == 0)
		return (FALSE);
	return (TRUE);
}

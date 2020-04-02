/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_sidedef.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 17:45:38 by Malou          #+#    #+#                */
/*   Updated: 2020/04/01 19:14:42 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

static t_intersect		calculate_intersect_point(t_point start_a, t_point start_b,
						t_point slope_a, t_point slope_b)
{
	t_intersect			intersect;
	double			denominator;
	double			t;
	double			s;

	intersect.x = NAN;
	intersect.y = NAN;
	denominator = (-slope_b.x * slope_a.y + slope_a.x * slope_b.y);
	if ((int)denominator == 0)
		return (intersect);
	s = (-slope_a.y * (start_a.x - start_b.x) + slope_a.x * \
		(start_a.y - start_b.y)) / denominator;
	t = (slope_b.x * (start_a.y - start_b.y) - slope_b.y * \
		(start_a.x - start_b.x)) / denominator;
	if (s > 0 && s < 1 && t > 0 && t < 1)
	{
		intersect.x = start_a.x + (t * slope_a.x);
		intersect.y = start_a.y + (t * slope_a.y);
	}
	intersect.x = fabs(intersect.x);
	intersect.y = fabs(intersect.y);
	return (intersect);
}

static t_intersect			find_intersection(t_point start_a, t_point end_a,
						t_point start_b, t_point end_b)
{
	t_point			intersect;
	t_point			slope_a;
	t_point			slope_b;

	intersect.x = 0.0;
	intersect.y = 0.0;
	slope_a.x = end_a.x - start_a.x;
	slope_a.y = end_a.y - start_a.y;
	slope_b.x = end_b.x - start_b.x;
	slope_b.y = end_b.y - start_b.y;
	return (calculate_intersect_point(start_a, start_b, slope_a, slope_b));
}

static double		intersect_distance(t_intersect intersect,
						t_line ray, double angle)
{
	double			distance;

	if (fabs(intersect.x - ray.start.x) > fabs(intersect.y - (int)ray.start.y))
		distance = (intersect.x - ray.start.x) / cos(angle);
	else
		distance = (intersect.y - ray.start.y) / sin(angle);
	return (distance);
}

void		find_sidedef(t_doom *doom, t_line ray, double angle, int sector, int column)
{
	t_intersect		intersect;
	t_intersect		min_intersect;
	double			distance;
	double			min_distance;
	int				prev_sector;
	int				x;

	x = 0;
	sector = 1;
	prev_sector = 1;
	min_distance = INFINITY;
	while (x < 5) //sidedefs in sector//
	{
		intersect = find_intersection(ray.start, ray.end,\
			doom->sidedef[x].start, doom->sidedef[x].end);
		distance = intersect_distance(intersect, ray, angle);
		if (distance < min_distance && distance > 0)
		{
			min_distance = distance;
			min_intersect.x = intersect.x;
			min_intersect.y = intersect.y;
			min_intersect.obj_dist = distance;
			min_intersect.sector = doom->sidedef[x].sector;
			min_intersect.opp_sector = doom->sidedef[x].opp_sector;
		}
		x++;
	}
	if (min_intersect.opp_sector != -1 && min_intersect.sector != prev_sector)
	{
		prev_sector = min_intersect.sector;
		find_sidedef(doom, ray, angle, min_intersect.opp_sector, column);
	}
	draw_column(doom, min_intersect, column);
}

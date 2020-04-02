/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_calculations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/02 12:09:58 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 13:15:13 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_intersect		line_intersection(t_point start2, t_point delta2,
						t_point start1, t_point delta1)
{
	t_intersect		intersect;
	double			denominator;
	double			t;
	double			s;

	intersect.point.x = NAN;
	intersect.point.y = NAN;
	denominator = (-delta2.x * delta1.y + delta1.x * delta2.y);
	if ((int)denominator == 0)
		return (intersect);
	s = (-delta1.y * (start1.x - start2.x) + delta1.x * \
		(start1.y - start2.y)) / denominator;
	t = (delta2.x * (start1.y - start2.y) - delta2.y * \
		(start1.x - start2.x)) / denominator;
	if (s > 0 && s < 1 && t > 0 && t < 1)
	{
		intersect.point.x = start1.x + (t * delta1.x);
		intersect.point.y = start1.y + (t * delta1.y);
	}
	intersect.point.x = fabs(intersect.point.x);
	intersect.point.y = fabs(intersect.point.y);
	return (intersect);
}

t_point			line_delta(t_point start, t_point end)
{
	t_point			delta;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	return (delta);
}

double		point_distance(t_point p1,
						t_point p2, double angle)
{
	double			distance;

	if (fabs(p1.x - p2.x) > fabs(p1.y - (int)p2.y))
		distance = (p1.x - p2.x) / cos(angle);
	else
		distance = (p1.y - p2.y) / sin(angle);
	return (distance);
}
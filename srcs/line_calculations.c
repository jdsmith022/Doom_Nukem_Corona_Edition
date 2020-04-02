/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_calculations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/02 12:09:58 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 15:42:57 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

t_intersect		line_intersection(t_point start1, t_point delta1,
						t_point start2, t_point delta2)
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

double		point_distance(t_point point1,
						t_point point2, double angle)
{
	double			distance;

	if (fabs(point1.x - point2.x) > fabs(point1.y - (int)point2.y))
		distance = (point1.x - point2.x) / cos(angle);
	else
		distance = (point1.y - point2.y) / sin(angle);
	return (distance);
}

double		line_intersection_distance(t_line line1, \
	t_line line2, double angle, t_intersect *intersect)
{
	double			distance;
	t_point			line1_delta;
	t_point			line2_delta;

	line1_delta = line_delta(line1.start, line1.end);
	line2_delta = line_delta(line2.start, line2.end);
	*intersect = line_intersection(line1.start, line1_delta,\
	line2.start, line2_delta);
	distance = point_distance(intersect->point, line1.start, angle);
	return (distance);
}
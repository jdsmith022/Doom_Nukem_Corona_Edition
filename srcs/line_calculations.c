/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   line_calculations.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/02 12:09:58 by Malou          #+#    #+#                */
/*   Updated: 2020/06/06 19:06:15 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"


t_point		line_intersection(t_point start1, t_point delta1,
						t_point start2, t_point delta2)
{
	t_point			intersect;
	double			denominator;
	double			t;
	double			s;

	intersect.x = NAN;
	intersect.y = NAN;
	denominator = (-delta2.x * delta1.y + delta1.x * delta2.y);
	if ((int)denominator == 0)
		return (intersect);
	s = (-delta1.y * (start1.x - start2.x) + delta1.x * \
		(start1.y - start2.y)) / denominator;
	t = (delta2.x * (start1.y - start2.y) - delta2.y * \
		(start1.x - start2.x)) / denominator;
	if (s > 0 && s < 1 && t > 0 && t < 1)
	{
		intersect.x = start1.x + (t * delta1.x);
		intersect.y = start1.y + (t * delta1.y);
	}
	intersect.x = fabs(intersect.x);
	intersect.y = fabs(intersect.y);
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
		distance = fabs((point1.x - point2.x) / cos(angle));
	else
		distance = fabs((point1.y - point2.y) / sin(angle));
	return (distance);
}

double		point_line_distance(t_point point, t_line line)
{
	double	denominator;
	t_point	delta;
	double 	distance;

	delta = line_delta(line.start, line.end);
	denominator = sqrt(pow(delta.y, 2) + pow(delta.x, 2));
	distance = delta.y * point.x - delta.x * point.y + line.end.x * line.start.y\
		- line.end.y * line.start.x / denominator;
	return (distance);
}
#include "../../includes/doom.h"

t_point		line_intersection(t_point start1, t_point delta1,
						t_point start2, t_point delta2)
{
	t_point	intersect;
	double	denominator;
	double	t;
	double	s;

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

t_point		line_delta(t_point start, t_point end)
{
	t_point	delta;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	return (delta);
}

double		point_distance(t_point point1,
				t_point point2, double angle)
{
	double	distance;

	if (fabs(point1.x - point2.x) > fabs(point1.y - (int)point2.y))
		distance = (point1.x - point2.x) / cos(angle);
	else
		distance = (point1.y - point2.y) / sin(angle);
	return (distance);
}

double		point_line_distance(t_point point, t_line line)
{
	double	denominator;
	t_point	delta;
	double	distance;
	t_point	closest_point;
	double	clip_dist;

	delta = line_delta(line.start, line.end);
	if (delta.x == 0 && delta.y == 0)
	{
		closest_point = line.start;
		delta = line_delta(line.start, point);
		return (sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
	}
	denominator = (pow(delta.x, 2) + pow(delta.y, 2));
	clip_dist = ((point.x - line.start.x) * delta.x +\
		(point.y - line.start.y) * delta.y) / denominator;
	if (clip_dist < 0)
		closest_point = line.start;
	else if (clip_dist > 1)
		closest_point = line.end;
	else
	{
		closest_point.x = line.start.x + clip_dist * delta.x;
		closest_point.y = line.start.y + clip_dist * delta.y;
	}
	delta = line_delta(closest_point, point);
	distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	return (distance);
}

double		points_distance(t_point p1, t_point p2)
{
	t_point delta;
	int		delta_pow_x;
	int		delta_pow_y;

	delta = line_delta(p1, p2);
	delta_pow_x = pow(delta.x, 2);
	delta_pow_y = pow(delta.y, 2);
	return (sqrt(delta_pow_x + delta_pow_y));
}

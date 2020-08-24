#include "../../includes/doom.h"

double			point_distance_angle(t_point point1,
				t_point point2, double angle)
{
	double	distance;

	if (fabs(point1.x - point2.x) > fabs(point1.y - (int)point2.y))
		distance = (point1.x - point2.x) / cos(angle);
	else
		distance = (point1.y - point2.y) / sin(angle);
	return (distance);
}

double			point_distance(t_point p1, t_point p2)
{
	t_point delta;
	int		delta_pow_x;
	int		delta_pow_y;

	delta = line_delta(p1, p2);
	delta_pow_x = pow(delta.x, 2);
	delta_pow_y = pow(delta.y, 2);
	return (sqrt(delta_pow_x + delta_pow_y));
}

static void		set_closest_point_to_line(t_point *point, t_line line,
	t_point delta, t_point *closest_point)
{
	double	denominator;
	double	clip_dist;

	denominator = (pow(delta.x, 2) + pow(delta.y, 2));
	clip_dist = ((point->x - line.start.x) * delta.x +\
		(point->y - line.start.y) * delta.y) / denominator;
	if (clip_dist < 0)
		*closest_point = line.start;
	else if (clip_dist > 1)
		*closest_point = line.end;
	else
	{
		closest_point->x = line.start.x + clip_dist * delta.x;
		closest_point->y = line.start.y + clip_dist * delta.y;
	}
}

double			point_line_distance(t_point point, t_line line)
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
	set_closest_point_to_line(&point, line, delta, &closest_point);
	delta = line_delta(closest_point, point);
	distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2));
	return (distance);
}

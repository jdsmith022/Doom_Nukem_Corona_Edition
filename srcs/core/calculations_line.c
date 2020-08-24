
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

double		get_line_angle(t_line line)
{
	t_point	delta;

	delta = line_delta(line.start, line.end);
	return (atan2(delta.y, delta.x));
}

t_point		check_line_intersection(t_line line1, t_line line2)
{
	t_point	intersect;
	t_point	line1_delta;
	t_point line2_delta;

	line1_delta = line_delta(line1.start, line1.end);
	line2_delta = line_delta(line2.start, line2.end);
	intersect = line_intersection(line1.start, line1_delta,\
	line2.start, line2_delta);
	return (intersect);
}

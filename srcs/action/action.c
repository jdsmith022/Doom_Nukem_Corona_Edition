#include "../../includes/doom.h"

int		init_poster(int x, double distance, t_point intersect,
			t_sidedef *poster)
{
	poster->distance = distance;
	poster->intersect = intersect;
	return (x);
}

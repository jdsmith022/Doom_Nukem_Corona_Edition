#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

int		init_poster(int x, double distance, t_point intersect,
			t_sidedef *poster)
{
	poster->distance = distance;
	poster->intersect = intersect;
	return (x);
}

void	relocate_moving_wall(t_point *intersect, t_sidedef *near_sidedef,
			t_doom *doom, int x)
{
	intersect->x -= doom->lib.sidedef[x + 1].line.end.x -\
		doom->lib.sidedef[x + 1].line.start.x;
	intersect->y -= doom->lib.sidedef[x + 1].line.end.y -\
		doom->lib.sidedef[x + 1].line.start.y;
	set_offset(near_sidedef, doom->lib.sidedef[x], *intersect, doom);
}

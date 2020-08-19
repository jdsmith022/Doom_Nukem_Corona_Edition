#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

void	check_virus_select(t_doom *doom)
{
	t_ray   ray;

	ray = init_ray(doom, MOUSE_X);
	check_hit(doom, ray, doom->i_sector, doom->i_sector);
	if (doom->own_event.virus_hit_index != -1)
		doom->hud->corona = TRUE;
}

int		init_poster(int x, double distance, t_point intersect,
			t_sidedef *poster)
{
	poster->distance = distance;
	poster->intersect = intersect;
	return (x);
}

void	relocate_poster(t_doom *doom, t_sidedef *poster)
{
	poster->intersect.x -= (int)poster->line.start.x % 16;
	poster->intersect.y -= (int)poster->line.start.y % 16;
	poster->intersect.x = (int)poster->intersect.x % 16;
	poster->intersect.y = (int)poster->intersect.y % 16;
	set_offset(poster, *poster, poster->intersect, doom);
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

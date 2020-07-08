#include "../../includes/doom.h"

static void		set_properties_plane_sky(t_doom *doom,
					t_plane *plane, int x)
{
	double		height_floor;
	int			sidedef_top;
	int			sidedef_bottom;
	int			div_height_std;
	int			new_height;

	distance *= cos(doom->ray_adjacent * x - FOV / 2);
	new_height = (HEIGHT + doom->player_height) / 2;
	plane->height_standard = doom->wall_height_std / distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	sidedef_top = (new_height - div_height_std) - doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (new_height + div_height_std) - doom->own_event.y_pitch;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}


void    sidedef_render_skybox(t_doom *doom, t_ray ray, t_line *sky_sd)
{
    t_point intersect;
    double  min_distance;
	t_plane plane;
    int x;

    x = 0;
    while (x < 4)
    {
        distance = sidedef_intersection_distance(ray,\
			sky_sd[x], &intersect);
		if (distance < min_distance)
			min_distance = distance;
		x++;
    }
	set_properties_plane_sky(doom, &plane, ray.plane_x)
	draw_skybox(doom, min_distance, intersect, ray)
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_sky_box.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:57 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 14:16:51 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void			set_properties_plane_sky(t_doom *doom,
						t_plane *plane, int x, double distance)
{
	double	height_floor;
	int		sidedef_top;
	int		sidedef_bottom;
	int		div_height_std;
	int		new_height;

	distance *= cos(doom->ray_adjacent * x - (60 * (PI / 180)) / 2);
	new_height = (HEIGHT + doom->player.height) / 2;
	plane->height_standard = doom->texture_height /\
		distance * doom->dist_to_plane;
	div_height_std = plane->height_standard / 2;
	sidedef_top = (new_height - div_height_std)\
		- doom->own_event.y_pitch;
	wall_offset(plane, sidedef_top);
	sidedef_bottom = (new_height + div_height_std)\
		- doom->own_event.y_pitch;
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

static void			set_properties(t_doom *doom, int set)
{
	doom->dir_angle = clamp_angle(doom->dir_angle);
	if (set == 0)
	{
		doom->texture_width = doom->lib.sky_lib[0]->w;
		doom->texture_height = doom->lib.sky_lib[0]->h;
		doom->player.std_height = 32;
	}
	else
	{
		doom->texture_width = 96;
		doom->texture_height = 96;
		doom->player.std_height = 48;
	}
}

static double		find_min_distance(t_doom *doom, t_ray ray,
					t_line *sky_sd, t_plane *plane)
{
	t_point	save_intersect;
	double	distance;
	double	min_distance;
	int		x;

	x = 0;
	min_distance = INFINITY;
	while (x < 4)
	{
		distance = sidedef_intersection_distance(ray,\
			sky_sd[x], &save_intersect);
		if (distance < min_distance)
		{
			min_distance = distance;
			plane->line = sky_sd[x];
			plane->intersect = save_intersect;
			set_properties(doom, 0);
		}
		x++;
	}
	return (min_distance);
}

static void			set_ray(t_ray *ray, t_doom *doom)
{
	ray->line.start.x = 64;
	ray->line.start.y = 64;
	ray->line.end.x = ray->line.start.x + doom->max_ray\
		* cos(ray->angle);
	ray->line.end.y = ray->line.start.y + doom->max_ray\
		* sin(ray->angle);
}

void				sidedef_render_skybox(t_doom *doom, t_ray ray,
					t_line *sky_sd)
{
	t_plane plane;
	double	min_distance;

	set_ray(&ray, doom);
	min_distance = find_min_distance(doom, ray, sky_sd, &plane);
	set_properties_plane_sky(doom, &plane, ray.plane_x, min_distance);
	draw_sky(doom, ray.plane_x, plane.sidedef_top);
	find_skybox_sidedef_texture(doom, ray.plane_x, plane);
	set_properties(doom, 1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sidedef_render.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 22:02:46 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 15:52:37 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

t_sidedef		set_properties_sidedef(t_point intersect, double distance,
						t_sidedef curr_sidedef, t_doom *doom)
{
	t_sidedef	sidedef;

	sidedef = curr_sidedef;
	sidedef.distance = distance;
	doom->texture_width = doom->lib.tex_lib[sidedef.txt_2]->w;
	doom->texture_height = doom->lib.tex_lib[sidedef.txt_2]->h;
	set_offset(&sidedef, curr_sidedef, intersect, doom);
	sidedef.intersect = intersect;
	sidedef.prev_sidedef = doom->prev_sidedef;
	return (sidedef);
}

double			sidedef_intersection_distance(t_ray ray,
					t_line line, t_point *intersect)
{
	double		distance;
	t_point		ray_delta;
	t_point		sidedef_delta;

	ray_delta = line_delta(ray.line.start, ray.line.end);
	sidedef_delta = line_delta(line.start, line.end);
	*intersect = line_intersection(ray.line.start, ray_delta,\
		line.start, sidedef_delta);
	distance = point_distance_angle(*intersect, ray.line.start, ray.angle);
	return (distance);
}

static void		next_sector_render(t_doom *doom, t_ray ray,
					t_render render, int sector)
{
	if (render.near_sidedef.opp_sector != -1 && \
	render.near_sidedef.opp_sector != doom->prev_sector)
	{
		doom->prev_sidedef.id = render.near_sidedef.id;
		doom->prev_sidedef.distance = render.near_sidedef.distance;
		doom->prev_sidedef.intersect = render.near_sidedef.intersect;
		sidedef_render(doom, ray, render.near_sidedef.opp_sector, sector);
	}
	doom->distance = render.min_distance;
	project_on_plane(doom, render.near_sidedef, ray.plane_x);
}

static void		set_near_sidedef_distance(t_doom *doom,
						t_render *render, int x)
{
	if (doom->lib.sidedef[x].action == 4 || doom->lib.sidedef[x].action == 8)
		render->near_sidedef.poster = \
			set_poster(doom, x, render->distance, render->intersect);
	else
	{
		render->min_distance = render->distance;
		render->near_sidedef = set_properties_sidedef(render->intersect,\
			render->distance, doom->lib.sidedef[x], doom);
	}
}

void			sidedef_render(t_doom *doom, t_ray ray, int sector,
					int prev_sector)
{
	t_render			render;
	int					x;

	doom->prev_sector = prev_sector;
	x = doom->lib.sector[sector].i_sidedefs;
	render.min_distance = INFINITY;
	if (doom->lib.sector[sector].action == OUTSIDE)
		sidedef_render_skybox(doom, ray, doom->lib.sky_sd);
	while (x < doom->lib.sector[sector].n_sidedefs +\
		doom->lib.sector[sector].i_sidedefs)
	{
		render.distance = sidedef_intersection_distance(ray,\
			doom->lib.sidedef[x].line, &render.intersect);
		if (render.distance <= render.min_distance &&\
		doom->lib.sidedef[x].opp_sector != doom->prev_sector)
			set_near_sidedef_distance(doom, &render, x);
		x++;
	}
	doom->stripe_distance[(int)ray.plane_x] = render.min_distance;
	sprite_check(doom, ray, sector, doom->prev_sector);
	if (render.min_distance != INFINITY)
		next_sector_render(doom, ray, render, sector);
}

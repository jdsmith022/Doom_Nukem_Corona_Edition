/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane_projections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:36 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 20:37:54 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void		set_sector_properties(t_doom *doom, t_sidedef sidedef,
					t_sector *sector, t_plane *plane)
{
	set_ceiling_limit(doom, sidedef, sector);
	set_floor_limit(doom, plane, sidedef, sector);
	if (sector->action == 1)
		doom->lib.portal_ceiling = plane->sidedef_top;
}

void			set_properties_plane(t_doom *doom, t_sidedef sidedef,
					t_plane *plane, t_sector *sector)
{
	t_sector	opp_sector;
	double		fov;

	fov = 60 * (PI / 180);
	sidedef.distance *= cos(doom->cast.ray_adjacent * plane->x - fov / 2);
	sidedef.prev_sidedef.distance *= \
		cos(doom->cast.ray_adjacent * plane->x - fov / 2);
	plane->intersect = sidedef.intersect;
	set_properties_plane_sidedef(doom, sidedef, *sector, plane);
	if (sidedef.opp_sector != -1)
	{
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			opp_sector, plane);
	}
	set_sector_properties(doom, sidedef, sector, plane);
}

static bool			in_range(int nb, int min, int max)
{
	if (nb > min && nb < max)
		return (TRUE);
	return (FALSE);
}

static t_clip			*same_sidedef(t_clip *head_node, int id)
{
	t_clip		*temp;

	temp = head_node;
	while (temp != NULL)
	{
		if (temp->sidedef == id)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

static void			set_values_clipping_sprites(t_doom *doom, t_plane plane,\
				t_sidedef sidedef, int x)
{
	t_clip		*node;
	t_clip		*node_bottom;
	t_clip		*top;
	t_clip		*temp;
	t_clip		*temp2;
	t_clip		*temp3;

	if (sidedef.opp_sector != -1 && sidedef.action != 6)
	{
		temp = same_sidedef(doom->clip->head_mid_bottom, sidedef.id);
		temp2 = same_sidedef(doom->clip->head_bottom, sidedef.id);
		temp3 = same_sidedef(doom->clip->head_top, sidedef.id);
		if (in_range(plane.mid_texture_bottom, -1, HEIGHT) && temp == NULL)
		{
			while (doom->clip->mid_bottom->next != NULL)
				doom->clip->mid_bottom = doom->clip->mid_bottom->next;
			node = new_clip_start(sidedef.sector, x, plane.mid_texture_bottom, sidedef.id);
			//protect
			doom->clip->mid_bottom->next = node;
		}
		else if (in_range(plane.mid_texture_bottom, -1, HEIGHT) && temp != NULL)
		{
			temp->line.end.x = x;
			temp->line.end.y = plane.mid_texture_bottom;
			doom->clip->mid_bottom->next->line.end = temp->line.end;
		}
		
		if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp2 == NULL)
		{
			while (doom->clip->bottom->next != NULL)
				doom->clip->bottom = doom->clip->bottom->next;
			node_bottom = new_clip_start(sidedef.sector, x, plane.sidedef_bottom, sidedef.id);
			//protect
			doom->clip->bottom->next = node_bottom;
		}
		else if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp2 != NULL)
		{
			temp2->line.end.x = x;
			temp2->line.end.y = plane.mid_texture_bottom;
			doom->clip->bottom->next->line.end = temp2->line.end;
			// doom->clip->bottom->next->line.end.x = x;
			// doom->clip->bottom->next->line.end.y =\
			plane.sidedef_bottom;
		}
		//TOP
		if (in_range(plane.sidedef_top, 0, HEIGHT) && temp3 == NULL)
		{
			while (doom->clip->top->next != NULL)
				doom->clip->top = doom->clip->top->next;
			top = new_clip_start(sidedef.sector, x, plane.sidedef_top, sidedef.id);
			//protect
			doom->clip->top->next = top;
		}
		else if (in_range(plane.sidedef_top, 0, HEIGHT) && temp3 != NULL)
		{
			temp3->line.end.x = x;
			temp3->line.end.y = plane.sidedef_top;
			doom->clip->top->next->line.end = temp3->line.end;
		}
	}
}

void			project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	plane.x = x;
	sector = doom->lib.sector[sidedef.sector];
	set_properties_plane(doom, sidedef, &plane, &sector);
	set_values_clipping_sprites(doom, plane, sidedef, x);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	else if (sidedef.action == WINDOW)
		save_window(doom, plane, sidedef, x);
	else if (sidedef.opp_sector != -1)
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (sector.action != OUTSIDE)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	draw_floor(doom, x, sector, plane.sidedef_bottom);
	if (sidedef.poster != -1)
		draw_poster(doom, plane, sidedef.poster, x);
}

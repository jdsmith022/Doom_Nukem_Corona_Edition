/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_nodes_clipping.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 21:00:38 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/08 16:06:12 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static bool		in_range(int nb, int min, int max)
{
	if (nb > min && nb < max)
		return (TRUE);
	return (FALSE);
}

static t_clip	*same_sidedef(t_clip *head_node, int id)
{
	t_clip		*temp;

	temp = head_node->next;
	while (temp != NULL)
	{
		if (temp->sidedef == id)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void			set_mid_bottom(t_doom *doom, t_plane plane, t_sidedef sidedef,
					int x)
{
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_mid_bottom, sidedef.id);
	if (in_range(plane.mid_texture_bottom, -1, HEIGHT) && temp == NULL)
	{
		while (doom->clip->mid_bottom->next != NULL)
			doom->clip->mid_bottom = doom->clip->mid_bottom->next;
		doom->clip->mid_bottom->next = new_clip_start(sidedef.sector, x,\
		plane.mid_texture_bottom, sidedef.id);
		if (!doom->clip->mid_bottom->next)
			doom_exit_failure(doom, "error: failed malloc\n");
	}
	else if (in_range(plane.mid_texture_bottom, 0, HEIGHT) && temp != NULL)
	{
		if (sidedef.id == temp->sidedef)
		{
			temp->line.end.x = x;
			temp->line.end.y = plane.mid_texture_bottom;
		}
	}
}

void			set_bottom(t_doom *doom, t_plane plane,
					t_sidedef sidedef, int x)
{
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_bottom, sidedef.id);
	if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp == NULL)
	{
		while (doom->clip->bottom->next != NULL)
			doom->clip->bottom = doom->clip->bottom->next;
		doom->clip->bottom->next = new_clip_start(sidedef.sector,\
		x, plane.sidedef_bottom, sidedef.id);
		if (!doom->clip->bottom->next)
			doom_exit_failure(doom, "error: failed malloc\n");
	}
	else if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp != NULL)
	{
		if (sidedef.id == temp->sidedef)
		{
			temp->line.end.x = x;
			temp->line.end.y = plane.mid_texture_bottom;
		}
	}
}

void			set_top(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_top, sidedef.id);
	if (in_range(plane.sidedef_top, 0, HEIGHT) && temp == NULL)
	{
		while (doom->clip->top->next != NULL)
			doom->clip->top = doom->clip->top->next;
		doom->clip->top->next = new_clip_start(sidedef.sector, x,\
		plane.sidedef_top, sidedef.id);
		if (!doom->clip->top->next)
			doom_exit_failure(doom, "error: failed malloc\n");
	}
	else if (in_range(plane.sidedef_top, 0, HEIGHT) && temp != NULL)
	{
		if (sidedef.id == temp->sidedef && sidedef.sector == temp->sector_id)
		{
			temp->line.end.x = x;
			temp->line.end.y = plane.sidedef_top;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_nodes_clipping.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 21:00:38 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/06 22:37:56 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static bool				in_range(int nb, int min, int max)
{
	if (nb > min && nb < max)
		return (TRUE);
	return (FALSE);
}

static t_clip			*same_sidedef(t_clip *head_node, int id)
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

void		set_mid_bottom(t_doom *doom, t_plane plane, t_sidedef sidedef,\
			int x)
{
	t_clip		*mid_bottom;
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_mid_bottom, sidedef.id);
	if (in_range(plane.mid_texture_bottom, -1, HEIGHT) && temp == NULL)
	{
		while (doom->clip->mid_bottom->next != NULL)
			doom->clip->mid_bottom = doom->clip->mid_bottom->next;
		mid_bottom = new_clip_start(sidedef.sector, x,\
		plane.mid_texture_bottom, sidedef.id);
		//protect
		doom->clip->mid_bottom->next = mid_bottom;
	}
	else if (in_range(plane.mid_texture_bottom, -1, HEIGHT) && temp != NULL)
	{
		if (sidedef.id == temp->sidedef)
		{
			temp->line.end.x = x;
			temp->line.end.y = plane.mid_texture_bottom;
			doom->clip->mid_bottom->next->line.end = temp->line.end;
		}
	}
}

void		set_bottom(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	t_clip		*bottom;
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_bottom, sidedef.id);
	if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp == NULL)
	{
		while (doom->clip->bottom->next != NULL)
			doom->clip->bottom = doom->clip->bottom->next;
		bottom = new_clip_start(sidedef.sector,\
		x, plane.sidedef_bottom, sidedef.id);
		//protect
		doom->clip->bottom->next = bottom;
	}
	else if (in_range(plane.sidedef_bottom, -1, HEIGHT) && temp != NULL)
	{
		temp->line.end.x = x;
		temp->line.end.y = plane.mid_texture_bottom;
		doom->clip->bottom->next->line.end = temp->line.end;
	}
}

void		set_top(t_doom *doom, t_plane plane, t_sidedef sidedef, int x)
{
	t_clip		*top;
	t_clip		*temp;

	temp = same_sidedef(doom->clip->head_top, sidedef.id);
	if (in_range(plane.sidedef_top, 0, HEIGHT) && temp == NULL)
	{
		while (doom->clip->top->next != NULL)
			doom->clip->top = doom->clip->top->next;
		top = new_clip_start(sidedef.sector, x,\
		plane.sidedef_top, sidedef.id);
		//protect
		doom->clip->top->next = top;
		// ft_bzero(temp, sizeof(t_clip));
	}
	else if (in_range(plane.sidedef_top, 0, HEIGHT) && temp != NULL)
	{
		if (sidedef.id == temp->sidedef && sidedef.sector == temp->sector_id)
		{
		// 	if (sidedef.id == 355)
		// 	{
		// 		printf("355: (%d;%d) id: %d sector: %d\n", x, plane.sidedef_top, temp->sidedef, temp->sector_id);
		// 	}
		// 	if (sidedef.id == 294)
		// 	{
		// 		printf("294: (%d;%d) id: %d sector: %d\n", x, plane.sidedef_top, temp->sidedef, temp->sector_id);
		// 	}
			temp->line.end.x = x;
			temp->line.end.y = plane.sidedef_top;
			// temp->next = NULL;
			doom->clip->top->next->line.end = temp->line.end;
		}
	}
}


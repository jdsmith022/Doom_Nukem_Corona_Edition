/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   create_sector.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 20:54:39 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		set_sector_sidedefs(t_doom *doom)
{
	t_ed_sidedef	*sidedef;
	int				i_sidedef;
	int				n_sidedefs;

	i_sidedef = -1;
	n_sidedefs = 0;
	sidedef = doom->game_design.sd_head;
	while (sidedef->next != NULL)
	{
		sidedef = sidedef->next;
		if (i_sidedef == -1 && sidedef->sector == doom->game_design.sc_len)
			i_sidedef = sidedef->id;
		if (sidedef->sector == doom->game_design.sc_len)
			n_sidedefs++;
	}
	doom->game_design.ed_sector->i_sidedefs = i_sidedef;
	doom->game_design.ed_sector->n_sidedefs = n_sidedefs;
}

void			set_ed_sector_values(t_doom *doom)
{
	t_ed_sector *prev;
	int			id;

	id = doom->game_design.sc_len;
	while (doom->game_design.ed_sector->next != NULL)
		doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->next = \
		(t_ed_sector*)ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector->next)
		doom_exit_failure(doom, "error: malloc sector in editor\n");
	prev = doom->game_design.ed_sector;
	doom->game_design.ed_sector = doom->game_design.ed_sector->next;
	doom->game_design.ed_sector->previous = prev;
	set_sector_sidedefs(doom);
	doom->game_design.ed_sector->height_floor = doom->game_design.floor_height;
	doom->game_design.ed_sector->height_ceiling =\
		doom->game_design.ceiling_height;
	doom->game_design.ed_sector->light_level = doom->game_design.light_level;
	doom->game_design.ed_sector->id = id;
	doom->game_design.ed_sector->next = NULL;
	doom->game_design.open_connection = TRUE;
	doom->game_design.sc_len++;
}

static void		create_mid_points(t_line *line)
{
	t_point center;

	center.x = (line->start.x + line->end.x) / 2;
	center.y = (line->start.y + line->end.y) / 2;
	if (line->start.x == line->end.x)
	{
		line->start.x = center.x;
		line->start.y = center.y + 5;
		line->end.x = center.x;
		line->end.y = center.y - 5;
	}
	else
	{
		line->start.x = center.x + 5;
		line->start.y = center.y;
		line->end.x = center.x - 5;
		line->end.y = center.y;
	}
}

static bool		get_portal(t_doom *doom, t_line *line)
{
	t_ed_sidedef *sidedef;

	sidedef = doom->game_design.ed_sidedef;
	while (sidedef != NULL && sidedef->opp_sector == -1)
		sidedef = sidedef->previous;
	if (sidedef == NULL || sidedef->line.start.x == 0)
		return (FALSE);
	*line = sidedef->line;
	return (TRUE);
}

bool			snap_close_sector(t_doom *doom, t_point start, t_point *end)
{
	double		distance;
	t_line		line;
	t_line		ray;

	get_portal(doom, &line);
	create_mid_points(&line);
	ray.start = line.start;
	ray = set_ray(doom, ray);
	if (check_sector_in_sector(doom, ray) == FALSE && \
	doom->game_design.sc_len > 0)
		return (FALSE);
	ray.start = line.end;
	ray = set_ray(doom, ray);
	if (check_sector_in_sector(doom, ray) == FALSE && \
	doom->game_design.sc_len > 0)
		return (FALSE);
	distance = point_distance(start, *end);
	if (distance < 10)
	{
		*end = start;
		return (TRUE);
	}
	return (FALSE);
}

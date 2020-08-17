#include "../../includes/doom.h"
#include "../../includes/action.h"

static int	check_collision(t_doom *doom, t_sidedef sidedef,
				t_line move)
{
	if (sidedef.opp_sector == -1 || \
	check_floor_diff(doom, doom->i_sector, sidedef.opp_sector) == TRUE ||
	doom->own_event.scissor_lift == TRUE)
		return (-1);
	else if (check_sector_height_diff(doom, doom->i_sector, \
	sidedef.opp_sector) == FALSE)
		return (-1);
	else if (sidedef.distance < 2 && \
	(sidedef.opp_sector == -1 || sidedef.action == 2))
		return (-1);
	else if (sidedef.opp_sector != -1)
	{
		doom->prev_sector = doom->i_sector;
		doom->i_sector = sidedef.opp_sector;
	}
	return (1);
}

static t_sidedef	sidedef_intersection(t_doom *doom, t_line move, \
	int sector, t_point prev_intersect)
{
	int				x;
	t_sidedef		sidedef;

	x = doom->lib.sector[sector].i_sidedefs;
	while (x < doom->lib.sector[sector].n_sidedefs\
		+ doom->lib.sector[sector].i_sidedefs)
	{
		sidedef = doom->lib.sidedef[x];
		sidedef.intersect = check_line_intersection(move, sidedef.line);
		sidedef.sector = sector;
		if (((isnan(sidedef.intersect.x) == 0 && \
			isnan(sidedef.intersect.y) == 0)) && \
			((sidedef.intersect.x != prev_intersect.x && \
			sidedef.intersect.y != prev_intersect.y)))
			return (sidedef);
		x++;
	}
	return (sidedef);
}

void	move_position(t_doom *doom, t_line move, double angle)
{
	t_sidedef	sidedef;
	t_point		prev_intersect;
	int			collision;

	if (sprite_collision(doom, move) == 1)
		return ;
	prev_intersect.x = -1;
	prev_intersect.y = -1;
	sidedef = sidedef_intersection(doom, move, doom->i_sector, prev_intersect);
	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
		doom->pos = move.end;
	else
		collision = check_collision(doom, sidedef, move);
	if (collision == 1)
	{
		prev_intersect = sidedef.intersect;
		sidedef = sidedef_intersection(doom, move, doom->i_sector, prev_intersect);
		if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
			doom->pos = move.end;
		else
			collision = check_collision(doom, sidedef, move);
		if (collision == -1)
			doom->i_sector = doom->prev_sector;
		if (collision == 0)
			doom->pos = move.end;
	}
	if (sidedef.action == 2 && point_distance(sidedef.intersect, doom->pos, angle) < 20.0)
		sliding_door(NULL, sidedef.id);
}


#include "../../includes/doom.h"
#include "../../includes/action.h"

static int	check_collision(t_doom *doom, t_sidedef sidedef,
				t_line move)
{
	if (sidedef.opp_sector == -1 || sidedef.action == 2)
		return (-1);
	if (check_floor_diff(doom, doom->i_sector, sidedef.opp_sector) == TRUE ||
	doom->own_event.scissor_lift == TRUE)
		return (-1);
	else if (check_sector_height_diff(doom, doom->i_sector, \
	sidedef.opp_sector) == FALSE)
		return (-1);
	return (0);
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
		printf("id = %d, intersect = %f, %f\n", sidedef.id, sidedef.intersect.x, sidedef.intersect.y);
		if (((isnan(sidedef.intersect.x) == 0 && \
			isnan(sidedef.intersect.y) == 0)) && \
			((sidedef.intersect.x != prev_intersect.x && \
			sidedef.intersect.y != prev_intersect.y)))
			return (sidedef);
		x++;
	}
	return (sidedef);
}

static t_sidedef	check_move_sidedef_intersection(t_doom *doom, t_line move, \
	int sector, t_point prev_intersect)
{
	t_sidedef	sidedef;
	int			collision;

	sidedef = sidedef_intersection(doom, move, sector, prev_intersect);
	printf("sector = %d, %f, %f\n", sidedef.sector, sidedef.intersect.x, sidedef.intersect.y);
	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
		doom->pos = move.end;
	else
	{
		collision = check_collision(doom, sidedef, move);
		printf("sidedef_id = %d, collision = %d\n", sidedef.id, collision);
		if (collision != -1)
		{
			prev_intersect = sidedef.intersect;
			sector = sidedef.opp_sector;
			check_move_sidedef_intersection(doom, move, sector, prev_intersect);
		}
	}
	doom->i_sector = sector;
	printf("return sector = %d\n", sector);
	return (sidedef);
}

void	move_position(t_doom *doom, t_line move, double angle)
{
	t_sidedef	sidedef;
	t_point		prev_intersect;

	move.start = doom->pos;
	prev_intersect.x = -1;
	prev_intersect.y = -1;
	if (sprite_collision(doom, move) == 1)
		return ;
	sidedef = check_move_sidedef_intersection(doom, move, \
		doom->i_sector, prev_intersect);
	if (sidedef.action == 2 && point_distance(sidedef.intersect, \
		doom->pos, angle) < 20.0)
		sliding_door(NULL, sidedef.id);
	// sidedef = sidedef_intersection(doom, move, doom->i_sector, prev_intersect)
	// if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
	// 	doom->pos = move.end;
	// else
	// 	collision = check_collision(doom, sidedef, move);
	// if (collision != -1)
	// {
	// 	prev_intersect = sidedef.intersect;
	// 	sidedef = sidedef_intersection(doom, move, doom->i_sector, prev_intersect);
	// 	if (isnan(sidedef.intersect.x) != 0 && isnan(sidedef.intersect.y) != 0)
	// 		doom->pos = move.end;
	// 	else
	// 		collision = check_collision(doom, sidedef, move);
	// 	if (collision == -1)
	// 		doom->i_sector = doom->prev_sector;
	// 	if (collision == 0)
	// 		doom->pos = move.end;
	// }
}


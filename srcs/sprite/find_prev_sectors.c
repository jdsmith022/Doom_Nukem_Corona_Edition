#include "../../includes/doom.h"
#include "../../includes/sprites.h"

t_point			sidedef_sprite_intersect(t_line sidedef, t_line sprite)
{
	t_point		sprite_delta;
	t_point		sidedef_delta;
	t_point		intersect;

	sprite_delta = line_delta(sprite.start, sprite.end);
	sidedef_delta = line_delta(sidedef.start, sidedef.end);
	intersect = line_intersection(sprite.start, sprite_delta,\
		sidedef.start, sidedef_delta);
	return (intersect);
}

static int		intersect_values(int opp_sector, int prev_sector,\
				t_point intersect)
{
	if ((!isnan(intersect.x) && !isnan(intersect.y))\
	&&/* opp_sector != prev_sector &&*/ opp_sector != -1)
		return (1);
	return (-1);
}

static int		add_prev_sector(t_sprite *sprite, int curr_sector, int x)
{
	if (curr_sector != sprite->sector && sprite->n_sector < 50)
	{
		sprite->prev_sectors[sprite->n_sector] = curr_sector;
		sprite->n_sector++;
		x = -2;
	}
	return (x);
}

static int		no_intersect(t_point intersect, int opp_sector,\
				int prev_sector, int sprite_sector)
{
	if (!isnan(intersect.x) && !isnan(intersect.y))
	{
		if (opp_sector != -1 && opp_sector != prev_sector\
		&& opp_sector != sprite_sector)
		{
			return (1);
		}
	}
	return (-1);
}

void		find_sidedef_intersect_per_sector(t_doom *doom,\
			t_sprite *sprite, int curr_sector, int prev_sector)
{
	t_point	intersect;
	int		x;
	int		opp_sector;
	t_line	line;

	line.start = doom->pos;
	line.end = sprite->pos;
	x = doom->lib.sector[curr_sector].i_sidedefs;
	opp_sector = doom->lib.sidedef[x].opp_sector;
	while (x >= 0 && x < doom->lib.sector[curr_sector].n_sidedefs +\
		doom->lib.sector[curr_sector].i_sidedefs)
	{
		intersect = sidedef_sprite_intersect(doom->lib.sidedef[x].line, line);
		if (intersect_values(opp_sector, prev_sector, intersect) == 1)
		{
			curr_sector = doom->lib.sidedef[x].sector;
			opp_sector = doom->lib.sidedef[x].opp_sector;
			x = add_prev_sector(sprite, curr_sector, x);
		}
		x++;
	}
	if (no_intersect(intersect, opp_sector, prev_sector, sprite->sector) == 1)
		find_sidedef_intersect_per_sector(doom, sprite, opp_sector,
		curr_sector);
}

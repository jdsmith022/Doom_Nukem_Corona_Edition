#include "../../includes/doom.h"
#include "../../includes/sprites.h"

t_point		sidedef_sprite_intersect(t_line sidedef, t_line sprite)
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

//the t_line line can be removed, that is from doom->pos to sprite->pos
void		find_sidedef_intersect_per_sector(t_doom *doom,\
			t_sprite *sprite, t_line line, int curr_sector, int prev_sector)
{
	t_point	intersect;
	int		x;
	int		opp_sector;

	x = doom->lib.sector[curr_sector].i_sidedefs;
	opp_sector = doom->lib.sidedef[x].opp_sector;
	while (x >= 0 && x < doom->lib.sector[curr_sector].n_sidedefs +\
		doom->lib.sector[curr_sector].i_sidedefs)
	{
		intersect = sidedef_sprite_intersect(doom->lib.sidedef[x].line, line);
		//this if statement can be in a sep function
		if ((!isnan(intersect.x) && !isnan(intersect.y))\
		&& doom->lib.sidedef[x].opp_sector != prev_sector &&\
		doom->lib.sidedef[x].opp_sector != -1)
		{
			curr_sector = doom->lib.sidedef[x].sector;
			opp_sector = doom->lib.sidedef[x].opp_sector;
			//from here
			if (curr_sector != sprite->sector)
			{
				sprite->prev_sectors[sprite->n_sector] = curr_sector;
				sprite->n_sector++;
				x = -2;
			}
			//to here can go in a sep function return x
		}
		x++;
	}
	if (!isnan(intersect.x) && !isnan(intersect.y))
	{
		if (opp_sector != -1 && opp_sector != prev_sector\
		&& opp_sector != sprite->sector)
		{
			find_sidedef_intersect_per_sector(doom, sprite, line,\
			opp_sector, curr_sector);
		}
	}
}

void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
{
	t_line		sprite_ray;

	sprite->n_sector = 0;
	sprite_ray.start = doom->pos;
	sprite_ray.end = sprite->pos;
	find_sidedef_intersect_per_sector(doom, sprite, sprite_ray,\
	doom->i_sector, doom->i_sector);
}

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;
	t_point sprite_begin;
	t_point sprite_end;

	i = 0;
	while (i < doom->visible_sprites)
	{
		index = sprite_order[i];
		if (doom->i_sector != doom->lib.sprites[index].sector)
			find_prev_sectors(doom, &doom->lib.sprites[index]);
		if (doom->own_event.window == TRUE)
		{
			// printf("draw sprite, window == TRUE\n");
			if (doom->lib.sprites[index].sector ==\
			doom->lib.window.curr_sector)
				draw_window_as_sprite(doom);
		}
		scale_sprite(doom, &sprite_begin, &sprite_end,\
		&doom->lib.sprites[index]);
		draw_stripes(doom, &sprite_begin, &sprite_end, index);
		doom->lib.sprites[index].visible = -1;
		i++;
	}
	ft_bzero(sprite_order, doom->visible_sprites);
	doom->visible_sprites = 0;
}

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	sprite_order = sort_sprite_array(doom->lib.sprites,\
	doom->visible_sprites, doom->total_sprites);
	draw_sprite(doom, sprite_order);
	free(sprite_order);
}

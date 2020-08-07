#include "../../includes/doom.h"

/*
**	Some sectors get ignored when there is a corner and the sprite is quite wide.
**	Solution is sending out another ray at the end of the sprite
*/

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

void		find_sidedef_intersect_per_sector(t_doom *doom,\
			t_sprite *sprite, t_line line, int curr_sector, int prev_sector)
{
	t_point	intersect;
	int		x;
	int		opp_sector;

	printf("begin find sidedef, sprite->n: %d\n", sprite->n_sector);
	printf("curr_sector: %d, prev_sector: %d\n", curr_sector, prev_sector);
	x = doom->lib.sector[curr_sector].i_sidedefs;
	printf("x: %d\n", x);
	opp_sector = doom->lib.sidedef[x].opp_sector;
	while (x >= 0 && x < doom->lib.sector[curr_sector].n_sidedefs +\
		doom->lib.sector[curr_sector].i_sidedefs)
	{
		printf("x %d\n", x);
		intersect = sidedef_sprite_intersect(doom->lib.sidedef[x].line, line);
		if ((!isnan(intersect.x) && !isnan(intersect.y))\
		&& doom->lib.sidedef[x].opp_sector != prev_sector &&\
		doom->lib.sidedef[x].opp_sector != -1)
		{
			curr_sector = doom->lib.sidedef[x].sector;
			printf("curr_sectr 2: %d\n", curr_sector);
			opp_sector = doom->lib.sidedef[x].opp_sector;
			printf("opp_sector in while: %d\n", opp_sector);
			if (curr_sector != sprite->sector)
			{
				sprite->prev_sectors[sprite->n_sector] = curr_sector;
				sprite->n_sector++;
				x = -2; //this is scary
			}
		}
		x++;
	}
	printf("eind find sidedef\n");
	if (!isnan(intersect.x) && !isnan(intersect.y))
	{
		if (/*opp_sector != -1 && */opp_sector != prev_sector && opp_sector != sprite->sector)
		{
			printf("curr_sector: %d\n", curr_sector);
			printf("opp_sector: %d\n", opp_sector);
			find_sidedef_intersect_per_sector(doom, sprite, line, opp_sector, curr_sector);
		}	
	}
}

void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
{
	t_line		sprite_ray;

	printf("find prev sectors start\n");
	sprite->n_sector = 0;
	sprite_ray.start = doom->pos;
	sprite_ray.end = sprite->pos;
	printf("befoore sidedef\n");
	find_sidedef_intersect_per_sector(doom, sprite, sprite_ray,\
	doom->i_sector, doom->i_sector);
	printf("after sidedef\n");
}

//remove
// void		print_prev_sectors(t_sprite sprite, int index)
// {
// 	int		i;

// 	i = 0;
// 	printf("For sprite #%d, sectors:\n", index);
// 	while (i < sprite.n_sector)
// 	{
// 		printf("%d ", sprite.prev_sectors[i]);
// 		i++;
// 	}
// 	printf("\n");
// }

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;
	t_point sprite_begin;
	t_point sprite_end;

	i = 0;
	printf("draw_sprite1\n");
	while (i < doom->visible_sprites)
	{
		printf("visible sprites = %d, i: %d\n", doom->visible_sprites, i);
		index = sprite_order[i];
		printf("index (from sprite_order : %d)\n", index);
		// ft_bzero(doom->lib.sprites[index].prev_sectors, 50); //yes or no?
		if (doom->i_sector != doom->lib.sprites[index].sector)
		{
			find_prev_sectors(doom, &doom->lib.sprites[index]);
			// print_prev_sectors(doom->lib.sprites[index], index);
		}
		printf("before scale sprite\n");
		scale_sprite(doom, &sprite_begin, &sprite_end,\
		&doom->lib.sprites[index]);
		draw_stripes(doom, &sprite_begin, &sprite_end, index);
		doom->lib.sprites[index].visible = -1;
		printf("i: %d\n", i);
		i++;
	}
	printf("after while draw sprite\n");
	doom->visible_sprites = 0;
}

/*
** free int order array
*/

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	sprite_order = sort_sprite_array(doom->lib.sprites,\
	doom->visible_sprites, doom->total_sprites);
	// printf("after sprite_order\n");
	draw_sprite(doom, sprite_order);
	// printf("after draw_Sprite\n");
}

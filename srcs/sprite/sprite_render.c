#include "../../includes/doom.h"

void		cast_ray_from_player_to_sprite(t_doom *doom,\
			t_sprite *sprite, t_ray ray, int curr_sector, int prev_sector)
{
	t_point	intersect;
	int		next_sector;
	int		x;
	double	min_distance;
	double	distance;
	int		opp_sector;

	x = doom->lib.sector[curr_sector].i_sidedefs;
	printf("sidedef: %d\n", x);
	min_distance = sprite->distance;
	while (x < doom->lib.sector[curr_sector].n_sidedefs +\
		doom->lib.sector[curr_sector].i_sidedefs)
	{
		distance = sidedef_intersection_distance(ray,\
			doom->lib.sidedef[x].line, &intersect);
		printf("check distance for sector: %d, sidedef %d\n", doom->lib.sidedef[x].sector, x);
		if (distance <= min_distance &&\
		doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			printf("distance of sidedef intersect is less than sprite distance\n");
			min_distance = distance;
			curr_sector = doom->lib.sidedef[x].sector;
			opp_sector = doom->lib.sidedef[x].opp_sector;
			//can I save less sectors?
			if (curr_sector != sprite->sector)
			{
				printf("curr_sector is not sprite sector, save curr sector %d\n", curr_sector);
				sprite->prev_sectors[sprite->n_sector] = curr_sector;
				sprite->n_sector++;
				opp_sector = doom->lib.sidedef[x].opp_sector;
			}
		}
		x++;
	}
	printf("min_distance %f, sprite_distance: %f\n", min_distance, sprite->distance);
	if (min_distance < sprite->distance)
	{
		printf("opp_sector: %d, prev_sector: %d\n", opp_sector, prev_sector);
		if (opp_sector != -1 && opp_sector != prev_sector)
			cast_ray_from_player_to_sprite(doom, sprite, ray, opp_sector,\
			curr_sector);
	}
}

void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
{
	t_ray	ray;

	sprite->n_sector = 0;
	// ray.angle = doom->dir_angle - (FOV / 2);
	ray.line.start = doom->pos;
	// ray.angle = clamp_angle(ray.angle);
	// doom->ray_angle = ray.angle;
	ray.angle = sprite->angle;
	ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
	ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
	cast_ray_from_player_to_sprite(doom, sprite, ray, doom->i_sector,\
	doom->i_sector); //sprite stuur ik al mee in doom
}

//remove
void		print_prev_sectors(t_sprite sprite, int index)
{
	int		i;

	i = 0;
	printf("For sprite #%d, sectors:\n", index);
	while (i < sprite.n_sector)
	{
		printf("%d ", sprite.prev_sectors[i]);
		i++;
	}
	printf("\n");
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
		// ft_bzero(doom->lib.sprites[index].prev_sectors, 50); //yes or no?
		if (doom->i_sector != doom->lib.sprites[index].sector)
		{
			find_prev_sectors(doom, &doom->lib.sprites[index]);
			print_prev_sectors(doom->lib.sprites[index], index);
		}
		scale_sprite(doom, &sprite_begin, &sprite_end,\
		&doom->lib.sprites[index], index);
		draw_stripes(doom, &sprite_begin, &sprite_end, index);
		doom->lib.sprites[index].visible = -1;
		i++;
	}
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
	draw_sprite(doom, sprite_order);
}

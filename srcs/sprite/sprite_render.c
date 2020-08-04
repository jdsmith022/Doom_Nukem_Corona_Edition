#include "../../includes/doom.h"

// double				sidedef_intersection_distance_sprite(t_ray ray,
// 						t_line line, t_point *intersect, int x)
// {
// 	double		distance;
// 	t_point		ray_delta;
// 	t_point		sidedef_delta;

// 	ray_delta = line_delta(ray.line.start, ray.line.end);
// 	if (x == 16)
// 	{
// 		printf("ray line start: (%f ; %f)\nray line end: (%f ; %f)\n", ray.line.start.x, ray.line.start.y, ray.line.end.x, ray.line.end.y);
// 		printf("ray_delta: (%f ; %f)\n", ray_delta.x, ray_delta.y);
// 	}
// 	sidedef_delta = line_delta(line.start, line.end);
// 	if (x == 16)
// 	{
// 		printf("sidedef_delta: (%f ; %f)\n", sidedef_delta.x, sidedef_delta.y);
// 	}
// 	*intersect = line_intersection(ray.line.start, ray_delta,\
// 		line.start, sidedef_delta);
// 	if (x == 16)
// 	{
// 		printf("intersect: (%f ; %f)\n", intersect->x, intersect->y);
// 	}
// 	distance = point_distance(*intersect, ray.line.start, ray.angle);
// 	return (distance);
// }

// void		cast_ray_from_player_to_sprite(t_doom *doom,\
// 			t_sprite *sprite, t_ray ray, int curr_sector, int prev_sector)
// {
// 	t_point	intersect;
// 	int		next_sector;
// 	int		x;
// 	double	min_distance;
// 	double	distance;
// 	double	temp_distance;
// 	int		opp_sector;

// 	x = doom->lib.sector[curr_sector].i_sidedefs;
// 	printf("sidedef: %d\n", x);
// 	min_distance = sprite->distance;
// 	while (x >= 0 && x < doom->lib.sector[curr_sector].n_sidedefs +\
// 		doom->lib.sector[curr_sector].i_sidedefs)
// 	{
// 		temp_distance = sidedef_intersection_distance_sprite(ray,\
// 			doom->lib.sidedef[x].line, &intersect, x);
// 		if (temp_distance)
// 			distance = temp_distance;
// 		printf("check distance (%f) for sector: %d, sidedef %d\nopp_sector: %d, prev_sector: %d\n", distance, doom->lib.sidedef[x].sector, x, doom->lib.sidedef[x].opp_sector, prev_sector);
// 		if (distance && distance <= min_distance &&\
// 		doom->lib.sidedef[x].opp_sector != prev_sector && doom->lib.sidedef[x].opp_sector != -1)
// 		{
// 			printf("distance of sidedef intersect is less than sprite distance\n");
// 			min_distance = distance;
// 			curr_sector = doom->lib.sidedef[x].sector;
// 			opp_sector = doom->lib.sidedef[x].opp_sector;
// 			//can I save less sectors?
// 			if (curr_sector != sprite->sector)
// 			{
// 				printf("curr_sector is not sprite sector, save curr sector %d\n", curr_sector);
// 				sprite->prev_sectors[sprite->n_sector] = curr_sector;
// 				sprite->n_sector++;
// 				x = -2; //dit kan weg denk ik
// 			}
// 		}
// 		x++;
// 	}
// 	printf("min_distance %f, sprite_distance: %f\n", min_distance, sprite->distance);
// 	if (min_distance < sprite->distance)
// 	{
// 		printf("opp_sector: %d, prev_sector: %d, x: %d\n", opp_sector, prev_sector, x - 1);
// 		if (opp_sector != -1 && opp_sector != prev_sector && opp_sector != sprite->sector)
// 			cast_ray_from_player_to_sprite(doom, sprite, ray, opp_sector,\
// 			curr_sector);
// 	}
// }

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
	int		next_sector;
	int		x;
	int		opp_sector;

	x = doom->lib.sector[curr_sector].i_sidedefs;
	while (x >= 0 && x < doom->lib.sector[curr_sector].n_sidedefs +\
		doom->lib.sector[curr_sector].i_sidedefs)
	{
		intersect = sidedef_sprite_intersect(doom->lib.sidedef[x].line, line);
		if ((!isnan(intersect.x) && !isnan(intersect.y))\
		&& doom->lib.sidedef[x].opp_sector != prev_sector &&\
		doom->lib.sidedef[x].opp_sector != -1)
		{
			curr_sector = doom->lib.sidedef[x].sector;
			opp_sector = doom->lib.sidedef[x].opp_sector;
			if (curr_sector != sprite->sector)
			{
				sprite->prev_sectors[sprite->n_sector] = curr_sector;
				sprite->n_sector++;
				x = -2;
			}
		}
		x++;
	}
	if (!isnan(intersect.x) && !isnan(intersect.y))
	{
		if (/*opp_sector != -1 && */opp_sector != prev_sector && opp_sector != sprite->sector)
			find_sidedef_intersect_per_sector(doom, sprite, line, opp_sector, curr_sector);
	}
}

// void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
// {
// 	t_ray	ray;

// 	sprite->n_sector = 0;
// 	// ray.angle = doom->dir_angle - (FOV / 2);
// 	ray.line.start = doom->pos;
// 	// ray.angle = clamp_angle(ray.angle);
// 	// doom->ray_angle = ray.angle;
// 	ray.angle = sprite->angle;
// 	ray.line.end.x = ray.line.start.x + sprite->distance * cos(ray.angle);
// 	ray.line.end.y = ray.line.start.y + sprite->distance * sin(ray.angle);
// 	// ray.line.end.x = ray.line.start.x + doom->max_ray * cos(ray.angle);
// 	// ray.line.end.y = ray.line.start.y + doom->max_ray * sin(ray.angle);
// 	cast_ray_from_player_to_sprite(doom, sprite, ray, doom->i_sector,\
// 	doom->i_sector); //sprite stuur ik al mee in doom
// }

void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
{
	t_line		sprite_ray;

	sprite->n_sector = 0;
	sprite_ray.start = doom->pos;
	sprite_ray.end = sprite->pos;
	find_sidedef_intersect_per_sector(doom, sprite, sprite_ray,\
	doom->i_sector, doom->i_sector);
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

#include "../../includes/doom.h"

//int i is gewoon index tel van 0 - 4
void		check_visibility_sprite(t_doom *doom, t_sprite *sprite, t_ray ray, int i, int sprite_i, int prev_sector)
{
	t_point	ray_delta;
	t_point sprite_delta;
	t_point intersect;
	double	curr_distance;
	double	temp_distance;

	temp_distance = INFINITY;
	curr_distance = 0;
	// loop through the four lines, which one is closer?
	while (i < 4)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(sprite->lines[i].start, sprite->lines[i].end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		sprite->lines[i].start, sprite_delta);
		// printf("ray: %f;%f\t%f;%f\n", ray.line.start.x, ray.line.start.y, ray.line.end.x, ray.line.end.y);
		// printf("sprite: %f;%f\t%f;%f\n", sprite->lines[i].start.x, sprite->lines[i].start.y, sprite->lines[i].end.x, sprite->lines[i].end.y);
		// printf("intersect: %f, %f\n", intersect.x, intersect.y);
		if (!isnan(intersect.x) && !isnan(intersect.y))
		{
			// printf("intersect x: %f\n", intersect.x);
			// printf("intersect y: %f\n", intersect.y);
			// printf("intersect\n");
			curr_distance = point_distance(doom->pos, intersect, ray.angle);
			if (curr_distance < temp_distance)
			{

				temp_distance = curr_distance;
				// sprite->visible = i;
				sprite->visible = sprite->textures[i];
			}
			sprite->distance = fabs(point_distance(doom->pos, sprite->pos, ray.angle));
		}
		i++;
	}
	// printf("sprite->visible: %d\n", sprite->visible);
	if (sprite->visible != -1)
	{
		// printf("sprite %d is visible\n", sprite_i);
		// set_offset_sprite(&sprite, intersect);
		doom->visible_sprites++;
		sprite->sprite_x = ray.plane_x;
		// sprite->prev_sector = prev_sector;
	}
	// printf("einde check visibility sprite\n");
}

void		sprite_check(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	//check line intersection with all not yet visible sprites
	int		i;
	int		x;
	int		sprite_i;

	i = 0;
	x = 0;
	sprite_i = doom->lib.sector[sector].i_objects; //dit moet ik checken
	
	// printf("sprite_i: %d, sector: %d, n_objects: %d\n", sprite_i, sector, doom->lib.sector[sector].n_objects);
	//TOTAL_SPRITES per sector
	// printf("sprite_check 1\n");
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprites[sprite_i].visible == -1)
		{
			// printf("test sprite check\n");
			//loop through every line of particular object, save closest distance and line segment
			check_visibility_sprite(doom, &doom->lib.sprites[sprite_i], ray, x, sprite_i, prev_sector);
		}
		i++;
		sprite_i++;
	}
}

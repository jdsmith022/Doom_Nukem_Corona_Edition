# include "../../includes/doom.h"
# include "../../includes/gameplay.h"

/*
**	Het is een recursieve functie dus ik kan niet zomaar -1 returnen.
MOUSE_X: 602
MOUSE_Y: 335
sprite_begin_x: 532.000000
sprite_end_x: 651.270764
sprite_begin_y: 283.729236
sprite_end_y: 403.000000
sprite is hit
virus in range #2 is hit
start check_hit
start find_virus
start check_hit
start find_virus
start check_hit
start find_virus
YOU HIT NOTHING!! Try again.
*/

int		virus_in_shooting_area(t_doom *doom, int sprite_i)
{
	printf("virus in shooting area\n");
	printf("MOUSE_X: %d\n", MOUSE_X);
	printf("MOUSE_Y: %d\n", MOUSE_Y);
	printf("sprite_begin_x: %f\n", SPRITES[sprite_i].sprite_begin.x);
	printf("sprite_end_x: %f\n", SPRITES[sprite_i].sprite_begin.x + SPRITES[sprite_i].width);
	printf("sprite_begin_y: %f\n", SPRITES[sprite_i].sprite_begin.y);
	printf("sprite_end_y: %f\n", SPRITES[sprite_i].sprite_begin.y + SPRITES[sprite_i].height);
	if (MOUSE_X >= (int)SPRITES[sprite_i].sprite_begin.x &&\
	MOUSE_X <= (int)SPRITES[sprite_i].sprite_begin.x + \
	(int)SPRITES[sprite_i].width &&\
	MOUSE_Y >= (int)SPRITES[sprite_i].sprite_begin.y &&\
	MOUSE_Y <= (int)SPRITES[sprite_i].sprite_begin.y + \
	(int)SPRITES[sprite_i].height)
	{
		printf("sprite is hit\n");
		return (sprite_i);
	}
	return (-1);
}

int		virus_in_range(t_doom *doom, t_ray ray, int sprite_i,\
			int prev_sector)
{
	int			i;
	t_point		ray_delta;
	t_point		sprite_delta;
	t_point		intersect;

	printf("start virus in range\n");
	i = 0;
	while (i < 4)
	{
		ray_delta = line_delta(ray.line.start, ray.line.end);
		sprite_delta = line_delta(SPRITES[sprite_i].lines[i].start, SPRITES[sprite_i].lines[i].end);
		intersect = line_intersection(ray.line.start, ray_delta,\
		SPRITES[sprite_i].lines[i].start, sprite_delta);
		if (isnan(intersect.x) && isnan(intersect.y))
		{
			if (virus_in_shooting_area(doom, sprite_i) == -1)
				return (-1);
			printf("virus in range #%d is hit\n", sprite_i);
			return (sprite_i);
		}
		i++;
	}
	return (-1);
}

int		find_virus(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	int		sprite_hit;
	int		i;
	int		sprite_i;
	int		temp_virus;
	double	temp_dist_sprite;

	printf("start find_virus\n");
	temp_dist_sprite = INFINITY;
	temp_virus = -1;
	sprite_hit = -1;
	i = 0;
	sprite_i = SECTORS[sector].i_objects;
	while (i < SECTORS[sector].n_objects)
	{
		if (SPRITES[sprite_i].action == 4)
			temp_virus = virus_in_range(doom, ray, sprite_i, prev_sector);
		if (temp_virus != -1 && SPRITES[temp_virus].distance < temp_dist_sprite)
		{
			temp_dist_sprite = SPRITES[temp_virus].distance;
			sprite_hit = temp_virus;
		}
		i++;
		sprite_i++;
	}
	return (sprite_hit);
}

int		check_hit(t_doom *doom, t_ray ray, int sector, int prev_sector)
{
	t_point		isect;
	int			safe_x;
	int			x;
	double		dist;
	double		min_dist;
	int			hit_virus;
	double		temp_dist_sprite;
	int			temp_virus;

	printf("start check_hit\n");
	temp_virus = -1;
	temp_dist_sprite = INFINITY;
	hit_virus = -1;
	x = SECTORS[sector].i_sidedefs;
	min_dist = INFINITY;
	while (x < SECTORS[sector].n_sidedefs + SECTORS[sector].i_sidedefs)
	{
		dist = sidedef_intersection_distance(ray, SIDEDEFS[x].line, &isect);
		if (dist <= min_dist && SIDEDEFS[x].opp_sector != prev_sector)
		{
			min_dist = dist;
			safe_x = x;
		}
		x++;
	}
	temp_virus = find_virus(doom, ray, sector, prev_sector);
	if (temp_virus != -1 && SPRITES[temp_virus].distance < temp_dist_sprite)
	{
		temp_dist_sprite = SPRITES[hit_virus].distance;
		hit_virus = temp_virus;
	}
	//check distance of hit sprite
	if (SIDEDEFS[safe_x].opp_sector != -1 &&
		SIDEDEFS[safe_x].opp_sector != prev_sector)
		check_hit(doom, ray, SIDEDEFS[safe_x].opp_sector, sector);
	return (hit_virus);
}


void    shoot(t_doom *doom, int x, int y)
{
    t_ray   ray;
    int     object;

	printf("x: %d, y: %d\n", x, y);
    ray = init_ray(doom, x);
    object = check_hit(doom, ray, doom->i_sector, doom->i_sector);
	if (object == -1)
		printf("YOU HIT NOTHING!! Try again.\n");
	else
	{
		printf("Object #%d has been hit\n", object);
		//change color to red for 5 seconds
		SPRITES[object].visible = 17;
		SPRITES[object].textures[0] = 17;
		SPRITES[object].textures[1] = 17;
		SPRITES[object].textures[2] = 17;
		SPRITES[object].textures[3] = 17;
		// SPRITES[object].action = 5;
		//let sprite dissapear
		//by setting it to FLAG 6
	}
	
	// if (object = -1)
		//nothing is hit
	// else
	// {
		//sprite[object] turns red for 5 seconds and then disappears
	// }
}

void	handle_shooting(t_doom *doom)
{
	if (!handle_mouse_state(doom))
		return ;
	shoot(doom, MOUSE_X, MOUSE_Y);
}

void	shooting(t_doom *doom)
{
	if (doom->own_event.shoot == TRUE)
	{
		if (MOUSE_PRESSED)
			handle_shooting(doom);
		else
			doom->own_event.mouse_state_switched = false;
	}
}
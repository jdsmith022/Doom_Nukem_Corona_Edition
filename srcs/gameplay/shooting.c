# include "../../includes/doom.h"
# include "../../includes/gameplay.h"
# include "../../includes/hud.h"
# include "../../includes/font.h"

void		add_mist_to_sanitizer(t_doom *doom)
{
	int				diff;
	
	diff = 0;
	if (doom->own_event.mist == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);//make own timer
		doom->own_event.mist = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);//send here
		if (diff == 0)
		{
			draw_add_on(doom, SPRAYING_HAND);
		}
	}
}

/*
**		timer for letting red virus disappear after 5 seconds
**		eventually you could send a function as parameter
**		if you put this function in a different file take font.h with you
*/
void		remove_red_virus(t_doom *doom)
{
	int				diff;

	diff = 0;
	if (doom->own_event.virus_red == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer); //make own timer
		doom->own_event.virus_red = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);//send here
		if (diff <= 3)
		{
			SPRITES[doom->own_event.virus_red_i].action = 6;
			doom->own_event.virus_red_i = -1;
		}
	}
}


int		virus_in_shooting_area(t_doom *doom, int sprite_i)
{
	if (MOUSE_X >= (int)SPRITES[sprite_i].sprite_begin.x &&\
	MOUSE_X <= (int)SPRITES[sprite_i].sprite_begin.x + \
	(int)SPRITES[sprite_i].width &&\
	MOUSE_Y >= (int)SPRITES[sprite_i].sprite_begin.y &&\
	MOUSE_Y <= (int)SPRITES[sprite_i].sprite_begin.y + \
	(int)SPRITES[sprite_i].height)
		return (sprite_i);
	return (-1);
}

int		virus_in_range(t_doom *doom, t_ray ray, int sprite_i,\
			int prev_sector)
{
	int			i;
	t_point		ray_delta;
	t_point		sprite_delta;
	t_point		intersect;

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
	double	current_dist_sprite;

	sprite_hit = doom->own_event.virus_hit_index;
	if (sprite_hit == -1)
		current_dist_sprite = INFINITY;
	else
		current_dist_sprite = SPRITES[sprite_hit].distance;
	temp_virus = -1;
	i = 0;
	sprite_i = SECTORS[sector].i_objects;
	while (i < SECTORS[sector].n_objects)
	{
		if (SPRITES[sprite_i].action == 4)
			temp_virus = virus_in_range(doom, ray, sprite_i, prev_sector);
		if (temp_virus != -1 && SPRITES[temp_virus].distance < current_dist_sprite)
		{
			current_dist_sprite = SPRITES[temp_virus].distance;
			sprite_hit = temp_virus;
		}
		i++;
		sprite_i++;
	}
	return (sprite_hit);
}

void		check_hit(t_doom *doom, t_ray ray, int sector, int prev_sector) //leave non-static
{
	t_point		isect;
	int			temp_x;
	int			x;
	double		dist;
	double		min_dist;
	int			hit_virus;
	double		current_dist_sprite;
	int			temp_virus;

	temp_x = -1; //I need to set it to something otherwise it segfaults
	printf("start check hit of %d\n", doom->own_event.virus_hit_index);
	temp_virus = -1;
	hit_virus = doom->own_event.virus_hit_index;
	if (hit_virus != -1)
	{
		printf("hit virus != -1\n");
		current_dist_sprite = SPRITES[hit_virus].distance;
		printf("current_dist_sprite = %f\n", current_dist_sprite);
	}
	else
	{
		printf("current_dist_sprite = INFINITY\n");
		current_dist_sprite = INFINITY;
	}
	x = SECTORS[sector].i_sidedefs;
	min_dist = INFINITY;
	printf("before while\n");
	while (x < SECTORS[sector].n_sidedefs + SECTORS[sector].i_sidedefs)
	{
		dist = sidedef_intersection_distance(ray, SIDEDEFS[x].line, &isect);
		if (dist <= min_dist && SIDEDEFS[x].opp_sector != prev_sector)
		{
			min_dist = dist;
			temp_x = x;
		}
		x++;
	}
	printf("after while\n");
	temp_virus = find_virus(doom, ray, sector, prev_sector);
	printf("after find virus: %d\n", temp_virus);
	printf("sector: %d, prev_sector: %d\n", sector, prev_sector);
	if (temp_virus != -1 && SPRITES[temp_virus].distance < current_dist_sprite)
	{
		printf("temp_virus != -1\n");
		current_dist_sprite = SPRITES[temp_virus].distance;
		printf("temp virus is closer than current, so new dust: %f\n", current_dist_sprite);
		doom->own_event.virus_hit_index = temp_virus;
	}
	printf("end of if statement\n");
	printf("save_x = %d\n", temp_x);
	//check distance of hit sprite
	if (temp_x != -1 && SIDEDEFS[temp_x].opp_sector != -1 &&
		SIDEDEFS[temp_x].opp_sector != prev_sector)
	{
		printf("check hit again\n, safe_x: %d\n", temp_x);
		check_hit(doom, ray, SIDEDEFS[temp_x].opp_sector, sector);
	}
	if (SPRITES[doom->own_event.virus_hit_index].action == 11 && SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
		// printf("index: %d\n", sprite_i);
		doom->own_event.toilet_paper = TRUE;
		printf("YOU GOT TOILET PAPER!!!!\n");
	}
	else if (SPRITES[doom->own_event.virus_hit_index].action == 12 && SPRITES[doom->own_event.virus_hit_index].distance < 100.0)
	{
			// printf("index: %d\n", sprite_i);
			doom->own_event.trolly = TRUE;
			doom->lib.sidedef[17].action = 0;
			printf("YOU GOT THE TROLLY!\n");
	}
	printf("the end\n");
}

void    shoot(t_doom *doom)
{
    t_ray   ray;

	// doom->own_event.mist = TRUE;
	// add_mist_to_sanitizer(doom);
	// doom->hud->sanitizer_shooting = TRUE;
	printf("start shoot\n");
    ray = init_ray(doom, MOUSE_X);
	printf("after init_ray, %d", MOUSE_X);
    check_hit(doom, ray, doom->i_sector, doom->i_sector);
	printf("how far: %d\n", doom->own_event.virus_hit_index);
	if (doom->own_event.virus_hit_index == -1)
		printf("YOU HIT NOTHING!! Try again.\n");
	else if (SPRITES[doom->own_event.virus_hit_index].distance > 100.00)
		;
	else if (SPRITES[doom->own_event.virus_hit_index].action == 9 && SPRITES[doom->own_event.virus_hit_index].distance < 150.0)
	{
		// printf("index: %d\n", sprite_i);
		doom->own_event.spray_shopper = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		printf("HIT SHOPPER!!!!\n");
	}
	else
	{
		printf("Object #%d has been hit\n", doom->own_event.virus_hit_index);
		printf("distance is: %f\n", SPRITES[doom->own_event.virus_hit_index].distance);
		//change color to red for 5 seconds
		SPRITES[doom->own_event.virus_hit_index].visible = 17;
		SPRITES[doom->own_event.virus_hit_index].textures[0] = 17;
		SPRITES[doom->own_event.virus_hit_index].textures[1] = 17;
		SPRITES[doom->own_event.virus_hit_index].textures[2] = 17;
		SPRITES[doom->own_event.virus_hit_index].textures[3] = 17;
		SPRITES[doom->own_event.virus_hit_index].action = 5;
		doom->own_event.virus_red_i = doom->own_event.virus_hit_index;
		doom->own_event.virus_red = TRUE;
		doom->own_event.virus_hit_index = -1;
		//let sprite dissapear
		//by setting it to FLAG 6
	}
}

void	shooting(t_doom *doom)
{
	printf("check shooting\n");
	if (doom->own_event.shoot == TRUE)
	{
		if (MOUSE_PRESSED)
		{
			printf("handle shooting\n");
			shoot(doom);
		}
	}
}
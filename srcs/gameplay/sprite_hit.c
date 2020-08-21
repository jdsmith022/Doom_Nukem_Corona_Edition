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
		if (SPRITES[sprite_i].action == 4 || SPRITES[sprite_i].action == 9 \
		|| SPRITES[sprite_i].action == 13 || SPRITES[sprite_i].action == 11)
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

static void		check_hit(t_doom *doom, t_ray ray, int sector, int prev_sector)
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
	temp_virus = -1;
	hit_virus = doom->own_event.virus_hit_index;
	if (hit_virus != -1)
		current_dist_sprite = SPRITES[hit_virus].distance;
	else
		current_dist_sprite = INFINITY;
	x = SECTORS[sector].i_sidedefs;
	min_dist = INFINITY;
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
	temp_virus = find_virus(doom, ray, sector, prev_sector);
	if (temp_virus != -1 && SPRITES[temp_virus].distance < current_dist_sprite)
	{
		current_dist_sprite = SPRITES[temp_virus].distance;
		doom->own_event.virus_hit_index = temp_virus;
	}
	if (temp_x != -1 && SIDEDEFS[temp_x].opp_sector != -1 &&
	SIDEDEFS[temp_x].opp_sector != prev_sector)
		check_hit(doom, ray, SIDEDEFS[temp_x].opp_sector, sector);
}

void    check_sprite_hit(t_doom *doom)
{
    t_ray   ray;

    ray = init_ray(doom, MOUSE_X);
	printf("hit checkt: %d -- %d\n", MOUSE_X, MOUSE_Y);
    check_hit(doom, ray, doom->i_sector, doom->i_sector);
	if (doom->own_event.virus_hit_index != -1)
		check_select_spray_sprite(doom); //select and shooting of all sprites
	else
		printf("NOT VIRUS HIT!! Try again.\n");
}

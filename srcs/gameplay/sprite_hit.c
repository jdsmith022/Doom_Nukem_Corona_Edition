#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"
#include "../../includes/sprites.h"

static int		find_sprite(t_doom *doom, t_ray ray, int sector,
					int prev_sector)
{
	int			sprite_hit;
	int			i;
	int			sprite_i;
	int			temp_sprite;
	double		current_dist_sprite;

	sprite_hit = doom->own_event.virus_hit_index;
	current_dist_sprite = get_sprite_dist(doom, sprite_hit);
	temp_sprite = -1;
	i = 0;
	sprite_i = doom->lib.sector[sector].i_objects;
	while (i < doom->lib.sector[sector].n_objects)
	{
		if (sprite_has_action(doom->lib.sprites[sprite_i]))
			temp_sprite = sprite_in_range(doom, ray, sprite_i, prev_sector);
		if (temp_sprite != -1 &&
		doom->lib.sprites[temp_sprite].distance < current_dist_sprite)
		{
			current_dist_sprite = doom->lib.sprites[temp_sprite].distance;
			sprite_hit = temp_sprite;
		}
		i++;
		sprite_i++;
	}
	return (sprite_hit);
}

static void		check_hit(t_doom *doom, t_ray ray, int sector,
					int prev_sector)
{
	t_point		isect;
	int			temp_x;
	int			x;
	double		dist;
	double		min_dist;
	int			hit_sprite;
	double		current_dist_sprite;
	int			temp_sprite;

	temp_x = -1; //I need to set it to something otherwise it segfaults
	temp_sprite = -1;
	hit_sprite = doom->own_event.virus_hit_index;
	if (hit_sprite != -1)
		current_dist_sprite = doom->lib.sprites[hit_sprite].distance;
	else
		current_dist_sprite = INFINITY;
	x = doom->lib.sector[sector].i_sidedefs;
	min_dist = INFINITY;
	while (x < doom->lib.sector[sector].n_sidedefs + doom->lib.sector[sector].i_sidedefs)
	{
		dist = sidedef_intersection_distance(ray, doom->lib.sidedef[x].line, &isect);
		if (dist <= min_dist && doom->lib.sidedef[x].opp_sector != prev_sector)
		{
			min_dist = dist;
			temp_x = x;
		}
		x++;
	}
	temp_sprite = find_sprite(doom, ray, sector, prev_sector);
	if (temp_sprite != -1 && doom->lib.sprites[temp_sprite].distance < current_dist_sprite)
	{
		current_dist_sprite = doom->lib.sprites[temp_sprite].distance;
		doom->own_event.virus_hit_index = temp_sprite;
	}
	if (temp_x != -1 && doom->lib.sidedef[temp_x].opp_sector != -1 && \
	doom->lib.sidedef[temp_x].opp_sector != prev_sector)
		check_hit(doom, ray, doom->lib.sidedef[temp_x].opp_sector, sector);
}

void			check_sprite_hit(t_doom *doom)
{
	t_ray	ray;

	ray = init_ray(doom, doom->own_event.hold_x);
	check_hit(doom, ray, doom->i_sector, doom->i_sector);
	if (doom->own_event.virus_hit_index != -1)
		check_select_spray_sprite(doom);
}

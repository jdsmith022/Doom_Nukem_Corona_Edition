#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"

int			sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	int		value;

	value = 0;
	if ((sprite.action == 7 && doom->own_event.scissor_lift == FALSE)\
	|| sprite.action == 9 || sprite.action == 12)
		value = 15;
	if (movement.end.x >= sprite.lines[0].start.x - value &&\
	movement.end.x <= sprite.lines[0].end.x + value &&\
	movement.end.y >= sprite.lines[1].start.y - value &&\
	movement.end.y <= sprite.lines[1].end.y + value)
		return (1);
	return (-1);
}

void		exit_scissor_lift(t_doom *doom)
{
	double		distance;

	distance = point_distance(doom->pos,\
	doom->lib.sprites[doom->save_scissor_lift].pos);
	if (distance > 60)
	{
		doom->save_scissor_lift = -1;
		doom->own_event.scissor_lift = FALSE;
	}
	else
	{
		doom->own_event.parked_too_close = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
	}
}

void		activate_scissor_lift(t_doom *doom, int index)
{
	doom->own_event.scissor_lift = TRUE;
	doom->lib.font_lib.bools.text = TRUE;
	doom->lib.font_lib.bools.scissor_lift = TRUE;
	doom->pos.x = doom->lib.sprites[index].pos.x;
	doom->pos.y = doom->lib.sprites[index].pos.y;
	doom->save_scissor_lift = index;
	doom->player_height += 10;
}

static void	check_walking(t_doom *doom, t_sprite shopper)
{
	double new_dist;

	if (doom->own_event.sprite_collision == FALSE)
	{
		doom->own_event.sprite_collision_dist = shopper.distance;
		doom->own_event.sprite_collision = TRUE;
		doom->hud->shopper = TRUE;
		doom->own_event.sprite_index = shopper.index;
	}
	else if (shopper.distance > doom->own_event.sprite_collision_dist\
	&& doom->own_event.sprite_collision == TRUE &&\
	doom->own_event.sprite_index == shopper.index)
	{
		doom->own_event.sprite_collision = FALSE;
		doom->own_event.sprite_collision_dist = -1;
		doom->own_event.sprite_index = -1;
	}
}

static void	check_sprite_distance2(t_doom *doom, int index)
{
	if (doom->lib.sprites[index].action == 2)
	{
		doom->hud->health_pack = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.health_pack = TRUE;
		doom->lib.sprites[index].action = 8;
	}
	else if (doom->lib.sprites[index].action == 3)
	{
		doom->hud->facemask = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		doom->lib.font_lib.bools.facemask = TRUE;
		doom->lib.sprites[index].action = 8;
	}
	else if (doom->lib.sprites[index].action == 10)
	{
		if (doom->own_event.scissor_lift == FALSE)
		{
			doom->lib.sprites[index].action = 8;
			doom->own_event.fall = TRUE;
		}
	}
}

static void	check_sprite_distance(t_doom *doom, int index)
{
	if (doom->lib.sprites[index].distance > 0.1 &&\
	doom->lib.sprites[index].distance < 50)
	{
		if (doom->lib.sprites[index].action == 9)
			check_walking(doom, doom->lib.sprites[index]);
		else if (doom->lib.sprites[index].action == 4)
		{
			doom->own_event.corona_hit = TRUE;
			doom->lib.sprites[index].action = 6;
		}
		else if (doom->lib.sprites[index].action == 1)
		{
			doom->hud->health_pack_plus = TRUE;
			doom->lib.font_lib.bools.text = TRUE;
			doom->lib.font_lib.bools.health_pack = TRUE;
			doom->lib.sprites[index].action = 8;
		}
		else if (doom->lib.sprites[index].action == 11)
		{
			doom->game_start_time += 60000;
			doom->lib.sprites[index].action = 8;
		}
		else
			check_sprite_distance2(doom, index);
	}
}

int			sprite_collision(t_doom *doom, t_line movement)
{
	int		x;
	int		sector;
	int		index;

	x = 0;
	sector = doom->i_sector;
	index = doom->lib.sector[sector].i_objects;
	while (x < doom->lib.sector[sector].n_objects)
	{
		if (doom->lib.sprites[index].block == 1)
		{
			if (doom->lib.sprites[index].distance < 70\
			&& doom->own_event.scissor_lift == FALSE &&\
			doom->lib.sprites[index].action == 7)
				activate_scissor_lift(doom, index);
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		check_sprite_distance(doom, index);
		index++;
		x++;
	}
	return (-1);
}

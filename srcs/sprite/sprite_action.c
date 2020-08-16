#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"
#include "../../includes/action.h"

int			sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	int		value;

	value = 0;
	if ((sprite.action == 7 && doom->own_event.scissor_lift == FALSE) || sprite.action == 9)
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
	//check cords and surroundings (no close walls)
	printf("EXIT SCISSOR LIFT\n");
	printf("put scissor lift back at original sport\n");
	//park scissor lift next to you
	// doom->lib.sprites[doom->save_scissor_lift].lines[0].start.x = doom->pos.x - 70;
	// doom->lib.sprites[doom->save_scissor_lift].lines[0].start.y = doom->pos.y - 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[0].end.x = doom->pos.x - 50;
	// doom->lib.sprites[doom->save_scissor_lift].lines[0].end.y = doom->pos.y - 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[1].start.x = doom->pos.x - 50;
	// doom->lib.sprites[doom->save_scissor_lift].lines[1].start.y = doom->pos.y - 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[1].end.x = doom->pos.x - 50;
	// doom->lib.sprites[doom->save_scissor_lift].lines[1].end.y = doom->pos.y + 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[2].start.x = doom->pos.x - 50;
	// doom->lib.sprites[doom->save_scissor_lift].lines[2].start.y = doom->pos.y + 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[2].end.x = doom->pos.x - 70;
	// doom->lib.sprites[doom->save_scissor_lift].lines[2].end.y = doom->pos.y + 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[3].start.x = doom->pos.x - 70;
	// doom->lib.sprites[doom->save_scissor_lift].lines[3].start.y = doom->pos.y + 10;
	// doom->lib.sprites[doom->save_scissor_lift].lines[3].end.x = doom->pos.x - 70;
	// doom->lib.sprites[doom->save_scissor_lift].lines[3].end.y = doom->pos.y - 10;
	//park yourself next to it
	distance = points_distance(doom->pos, doom->lib.sprites[doom->save_scissor_lift].pos);
	if (distance > 75/* && distance < 100*/)
	{
		doom->save_scissor_lift = -1;
		doom->lib.font_lib.bools.text = FALSE;
		doom->own_event.scissor_lift_down = FALSE;
		doom->own_event.scissor_lift = FALSE;
	}
	else
	{
		//ADD FLAG
		doom->own_event.parked_too_close = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		printf("Please move further away from scissor lift parking spot\ndistance: %f\n", distance);
	}
}

void		activate_scissor_lift(t_doom *doom, int index)
{
	doom->own_event.scissor_lift = TRUE;
	doom->lib.font_lib.bools.text = TRUE;
	doom->pos.x = doom->lib.sprites[index].pos.x;
	doom->pos.y = doom->lib.sprites[index].pos.y;
	doom->own_event.y_pitch = 0;
	doom->save_scissor_lift = index;
	doom->player_height += 10;
	//deactivate jumping
	//doom->pos = sprite pos
	//add a bit of height
	//dont detect sprite scissor lift
	//add scissor_lift_bar to hud from HEIGHT - 55 draw start
	//you can't leave sector
	//moving up and down

	//if completely down you walk out
		//activate jumping
		//remove scissor_lift_bar from hud
		//deactivatie moving up an down
}

static void	check_walking(t_doom *doom, t_sprite shopper)
{
	double new_dist;

	// printf("top: %d, %f, %d\n", doom->own_event.sprite_collision, shopper.distance, doom->own_event.sprite_collision_dist);
	if (doom->own_event.sprite_collision == FALSE)
	{
		// printf("dist: %d\n", doom->own_event.sprite_collision_dist);
		doom->own_event.sprite_collision_dist = shopper.distance;
		doom->own_event.sprite_collision = TRUE;
		doom->hud->shopper = TRUE;
		doom->own_event.sprite_index = shopper.index;
	}
	else if (shopper.distance > doom->own_event.sprite_collision_dist && doom->own_event.sprite_collision == TRUE && doom->own_event.sprite_index == shopper.index)
	{
		// printf("compare: %d, %f\n", doom->own_event.sprite_collision_dist, shopper.distance);
		// printf("true\n");
		doom->own_event.sprite_collision = FALSE;
		doom->own_event.sprite_collision_dist = -1;
		doom->own_event.sprite_index = -1;
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
			doom->hud->corona = TRUE;
			doom->lib.sprites[index].action = 6;
		}
		else if (doom->lib.sprites[index].action == 1)
		{
			doom->hud->health_pack_plus = TRUE;
			doom->lib.sprites[index].action = 8;
		}
		else if (doom->lib.sprites[index].action == 2)
		{
			doom->hud->health_pack = TRUE;
			doom->lib.sprites[index].action = 8;
		}
		else if (doom->lib.sprites[index].action == 3)
		{
			doom->hud->facemask = TRUE;
			doom->lib.sprites[index].action = 8;
		}
		else if (doom->lib.sprites[index].action == 10)
			player_fall(doom, &doom->lib.sprites[index]);
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
			{
				printf("YOU ENTER THE SCISSOR LIFT\n");
				activate_scissor_lift(doom, index);
				printf("after enter scissor lift if statement\n");
			}
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		check_sprite_distance(doom, index);
		index++;
		x++;
	}
	return (-1);
}

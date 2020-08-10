#include "../../includes/doom.h"
#include "../../includes/hud.h"

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
		doom->own_event.scissor_lift_down = FALSE;
		doom->own_event.scissor_lift = FALSE;
		printf("deactivate scissor lift\n");
	}
	else
	{
		printf("Please move further away from scissor lift parking spot\ndistance: %f\n", distance);
	}
	// else
	// {
		// printf("Please go back to the parking spot of the scissor lift.");
	// }
}

void		activate_scissor_lift(t_doom *doom, int index)
{
	printf("activate scissor lift\n");
	doom->own_event.scissor_lift = TRUE;
	doom->pos.x = doom->lib.sprites[index].pos.x;
	doom->pos.y = doom->lib.sprites[index].pos.y;
	doom->save_scissor_lift = index;
	doom->player_height += 10;
	printf("CHANGED CORDS\n");
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
				printf("getting closer than 70\n");
				// if (doom->lib.sprites[index].action == 7)
				// {
					// printf("action == 7\n");
					// if (doom->own_event.scissor_lift == FALSE)
					// {
						printf("YOU ENTER THE SCISSOR LIFT\n");
						activate_scissor_lift(doom, index);
					// }
					printf("after enter scissor lift if statement\n");
				// }
			}
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		if (doom->lib.sprites[index].distance > 0.1 &&\
		doom->lib.sprites[index].distance < 50)
		{
			if (doom->lib.sprites[index].action == 9)
			{
				doom->hud->shopper = TRUE;
			}
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
		}
		index++;
		x++;
	}
	return (-1);
}

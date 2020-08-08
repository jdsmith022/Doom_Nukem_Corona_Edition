#include "../../includes/doom.h"
#include "../../includes/hud.h"

int			sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	int		value;

	value = 0;
	if ((sprite.action == 7 && doom->scissor_lift == FALSE) || sprite.action == 9)
		value = 15;
	if (movement.end.x >= sprite.lines[0].start.x - value &&\
	movement.end.x <= sprite.lines[0].end.x + value &&\
	movement.end.y >= sprite.lines[1].start.y - value &&\
	movement.end.y <= sprite.lines[1].end.y + value)
		return (1);
	else
		return (-1);
}

void		activate_scissor_lift(t_doom *doom, int index)
{
	doom->scissor_lift = TRUE;
	doom->pos.x = doom->lib.sprites[index].pos.x;
	doom->pos.y = doom->lib.sprites[index].pos.y;
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
			if (doom->lib.sprites[index].distance < 70)
			{
				if (doom->lib.sprites[index].action == 7)
				{
					printf("YOU ENTER THE SCISSOR LIFT\n");
					if (doom->scissor_lift == FALSE)
						activate_scissor_lift(doom, index);
				}
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

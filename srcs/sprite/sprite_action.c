#include "../../includes/doom.h"
#include "../../includes/hud.h"

int			sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	int		value;

	value = 0;
	if (sprite.action == 7 || sprite.action == 9)
		value = 15;
	if (movement.end.x >= sprite.lines[0].start.x - value &&\
	movement.end.x <= sprite.lines[0].end.x + value &&\
	movement.end.y >= sprite.lines[1].start.y - value &&\
	movement.end.y <= sprite.lines[1].end.y + value)
		return (1);
	else
		return (-1);
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
					// activate_scissor_lift()
				}
			}
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		if (doom->lib.sprites[index].distance < 50)
		{
			if (doom->lib.sprites[index].action == 9)
			{
				doom->hud->shopper = TRUE;
				printf("INCREASE CORONA LEVEL, SHOPPER %d\n", index);
			}
			else if (doom->lib.sprites[index].action == 4)
			{
				doom->hud->corona = TRUE;
				printf("INCREASE CORONA LEVEL! thanks to sprite %d\n", index);
				doom->lib.sprites[index].action = 6;
			}
			else if (doom->lib.sprites[index].action == 1)
			{
				doom->hud->health_pack = TRUE;
				printf("You've found a health pack plus!\n\
				Decrease Corona level with insane amount\n\
				Set action flag to 8 == inactive health sprite\n");
				doom->lib.sprites[index].action = 8;
			}
			else if (doom->lib.sprites[index].action == 2)
			{
				doom->hud->health_pack = TRUE;
				printf("You've found a health pack!\n\
				Decrease Corona level with moderate amount\n\
				Set action flag to 8 == inactive health sprite\n");
				doom->lib.sprites[index].action = 8;
			}
			else if (doom->lib.sprites[index].action == 3)
			{
				doom->hud->facemask = TRUE;
				printf("You've found a face mask!\n\
				Decrease Corona level with just a lil bit\n\
				Set action flag to 8 == inactive health sprite\n");
				doom->lib.sprites[index].action = 8;
			}
		}
		index++;
		x++;
	}
	return (-1);
}

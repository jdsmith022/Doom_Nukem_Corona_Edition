#include "../../includes/doom.h"

int			sprite_is_hit(t_doom *doom, t_line movement, t_sprite sprite)
{
	if (movement.end.x >= sprite.lines[0].start.x &&\
	movement.end.x <= sprite.lines[0].end.x &&\
	movement.end.y >= sprite.lines[1].start.y &&\
	movement.end.y <= sprite.lines[1].end.y)
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
					printf("YOU ENTER THE SCISSOR LIFT\n");
				else if (doom->lib.sprites[index].action == 9)
					printf("INCREASE CORONA LEVEL, SHOPPER %d\n", index);
			}
			if (sprite_is_hit(doom, movement, doom->lib.sprites[index]) == 1)
				return (1);
		}
		if (doom->lib.sprites[index].distance < 50)
		{
			if (doom->lib.sprites[index].action == 4)
			{
				printf("INCREASE CORONA LEVEL! thanks to sprite %d\n", index);
				doom->lib.sprites[index].action = 6;
			}
			else if (doom->lib.sprites[index].action == 1)
			{
				printf("You've found a health pack plus!\n\
				Decrease Corona level with insane amount\n\
				Set action flag to 8 == inactive health sprite\n");
				doom->lib.sprites[index].action = 8;
			}
			else if (doom->lib.sprites[index].action == 2)
			{
				printf("You've found a health pack!\n\
				Decrease Corona level with moderate amount\n\
				Set action flag to 8 == inactive health sprite\n");
				doom->lib.sprites[index].action = 8;
			}
			else if (doom->lib.sprites[index].action == 3)
			{
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

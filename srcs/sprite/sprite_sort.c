#include "../../includes/doom.h"

void		init_sprite_order_array(t_sprite *sprite, int *order,\
			int visible_sprites, int total_sprites)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	printf("\n");
	while (i < visible_sprites)
	{
		while (sprite[x].visible == -1 && x < total_sprites)
			x++;
		order[i] = x;
		printf("%d ", order[i]);
		x++;
		i++;
	}
	printf("\n");
}

void		sort_sprites(t_sprite *sprite, int *sprite_order, int total)
{
	int		i;
	int		x;
	int		nb;
	int		temp;

	x = 0;
	i = 0;
	nb = 1;
	temp = 0;
	while (i < total)
	{
		x = 0;
		while (x < total - nb)
		{
			if (sprite[sprite_order[x]].distance <\
			sprite[sprite_order[x + 1]].distance)
			{
				temp = sprite_order[x];
				sprite_order[x] = sprite_order[x + 1];
				sprite_order[x + 1] = temp;
			}
			x++;
		}
		i++;
	}
}

int			*sort_sprite_array(t_sprite *sprite, int visible_sprites,\
			int total_sprites)
{
	int		*sprite_order;
	int		i;

	sprite_order = (int*)malloc(sizeof(int) * visible_sprites);
	init_sprite_order_array(sprite, sprite_order, visible_sprites,\
	total_sprites);
	sort_sprites(sprite, sprite_order, visible_sprites);
	return (sprite_order);
}

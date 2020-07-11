#include "../../includes/doom.h"

void		init_sprite_order_array(t_sprite *sprite, int *order, int total)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (i < total)
	{
		while (sprite[x].visible == -1 && x < total - 1)
			x++;
		order[i] = x;
		x++;
		i++;
	}
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

int			*sort_sprite_array(t_sprite *sprite, int total)
{
	int		*sprite_order;
	int		i;

	printf("sort_sprite1, total: %d\n", total);
	sprite_order = (int*)malloc(sizeof(int) * total);
	// printf("sort_sprite2, total: %d\n", total);
	init_sprite_order_array(sprite, sprite_order, total);
	i = 0;
	// while (i < total)
	// {
	// 	printf("%d ", sprite_order[i]);
	// 	i++;
	// }
	// if (i < 0)
	// 	printf("sprite[i].distance: %f\n", sprite[0].distance);
	sort_sprites(sprite, sprite_order, total);
	return (sprite_order);
}

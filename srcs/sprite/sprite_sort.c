/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_sort.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:53:46 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/08 20:20:15 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		init_sprite_order_array(t_sprite *sprite, int *order,\
			int visible_sprites, int total_sprites)
{
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (i < visible_sprites)
	{
		while (sprite[x].visible == -1 && x < total_sprites)
			x++;
		order[i] = x;
		x++;
		i++;
	}
}

void		sort_sprites(t_sprite *sprite, int *sprite_order,\
			int total)
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

void		sort_sprites_window(int *sprite_order, int curr_sector,\
			int visible_sprites, t_sprite *sprite)
{
	int		i;
	int		temp;
	int		x;

	i = 0;
	x = 0;
	temp = 0;
	while (i < visible_sprites)
	{
		x = 0;
		while (x < visible_sprites - 1)
		{
			if (sprite[sprite_order[x]].sector == curr_sector &&\
			sprite[sprite_order[x + 1]].sector != curr_sector)
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

	sprite_order = (int*)ft_memalloc(sizeof(int) * visible_sprites);
	init_sprite_order_array(sprite, sprite_order, visible_sprites,\
	total_sprites);
	sort_sprites(sprite, sprite_order, visible_sprites);
	return (sprite_order);
}

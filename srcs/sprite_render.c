/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_render.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 14:55:53 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/04 12:54:48 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		scale_sprite(t_doom *doom, t_sprite *sprite)
{
	double		h;
	double		w;

	h = doom->sprite_image[sprite->index]->h;
	w = doom->sprite_image[sprite->index]->w;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	sprite->width = (sprite->height / h) * w;
}

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;

	i = 0;
	printf("%d\n", doom->visible_sprites);
	while (i < doom->visible_sprites)
	{
		index = sprite_order[i];
		//scale sprites
		scale_sprite(doom, &doom->sprite[index]);
		printf("height: %f\nwidth: %f\n", doom->sprite[index].height, doom->sprite[index].width);

		//find position on screen
		// find_position(doom, index);
		// draw_stripes(doom, index);
		// turn visibility off
		doom->sprite[index].visible = 0;
		i++;
	}
	doom->visible_sprites = 0;
}

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	//sort sprite array
	sprite_order = sort_sprite_array(doom->sprite, doom->visible_sprites);

	//draw sprites
	draw_sprite(doom, sprite_order);
	//(scale sprite and find_position))
		//turn visibility off
		//set doom->visible_sprite to 0
		//free sprite_order
}

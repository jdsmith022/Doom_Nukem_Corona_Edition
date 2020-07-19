/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_render.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 14:55:53 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/19 16:15:59 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		scale_sprite(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, t_sprite *sprite)
{
	double		h;
	double		w;
	int			new_height;
	double		height_std;
	int			div_height_std;
	double		height_floor;
	int			sidedef_bottom;
	int			wall_height_std;
	int			wall_diff_height_std;

	new_height = (HEIGHT + doom->player_height) / 2;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	wall_height_std = doom->wall_height_std / sprite->distance * doom->dist_to_plane;
	div_height_std = sprite->height / 2;
	wall_diff_height_std = wall_height_std / 2;	
	height_floor = doom->lib.sector[sprite->sector].height_floor / sprite->distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + wall_diff_height_std) - doom->own_event.y_pitch - height_floor;
	sprite_end->y = sidedef_bottom;
	sprite_begin->y = sprite_end->y - sprite->height;
	
	// sprite_begin->y = (new_height - div_height_std) - doom->own_event.y_pitch;
	// sprite_end->y = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	// sprite_begin->y = (new_height + div_height_std) - doom->own_event.y_pitch - height_floor;
	// sprite_end->y = sprite_begin->y + sprite->height;
	h = doom->lib.obj_lib[sprite->index]->h;
	w = doom->lib.obj_lib[sprite->index]->w;
	printf("h: %f, w: %f\n", h, w);
	// sprite->height = (sprite->size / sprite->distance * doom->dist_to_plane);
	// sprite->width = (sprite->size / sprite->distance * doom->dist_to_plane);
	sprite->width = (sprite->height / h) * w;
	printf("screen h: %f, screen w: %f\n", sprite->height, sprite->width);
	sprite_begin->x = sprite->sprite_x;
	sprite_end->x = sprite_begin->x + sprite->width;
	if (sprite_begin->x < 0)
		sprite_begin->x = 0;
	if (sprite_end->x > WIDTH)
		sprite_end->x = WIDTH - 1;
}

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;
	t_point sprite_begin;
	t_point sprite_end;

	i = 0;
	// printf("draw_sprite %d\n", doom->visible_sprites);
	while (i < doom->visible_sprites)
	{
		// printf("*index: %d\n", sprite_order[i]);
		index = sprite_order[i];
		//scale sprites
		scale_sprite(doom, &sprite_begin, &sprite_end, &doom->lib.sprites[index]);
		// printf("height: %f\nwidth: %f\n", doom->lib.sprites[index].height, doom->lib.sprites[index].width);

		//find position on screen
		// find_position(doom, &sprite_begin, &sprite_end, index);
			//sector portals (niet vergeten, niet opslaan als een muur)
			//in sidedef render opslaan
			//set_wall_properties (plane_projections)
		draw_stripes(doom, &sprite_begin, &sprite_end, index);
		// turn visibility off
		doom->lib.sprites[index].visible = 0;
		i++;
	}
	doom->visible_sprites = 0;
}

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	// printf("sprite_render 1\n");
	//sort sprite array
	// printf("visible sprites: %d\n", doom->visible_sprites);
	sprite_order = sort_sprite_array(doom->lib.sprites, doom->visible_sprites);

	// printf("sprite_render 2\n");
	//draw sprites
	draw_sprite(doom, sprite_order);
	//(scale sprite and find_position))
		//turn visibility off
		//set doom->visible_sprite to 0
		//free sprite_order
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_render.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/07 14:55:53 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/22 12:14:57 by rsteigen      ########   odam.nl         */
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
	int			plane_height_std;
	int			wall_diff_height_std;

	new_height = (HEIGHT + doom->player_height) / 2;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	plane_height_std = doom->wall_height_std / sprite->distance * doom->dist_to_plane;
	div_height_std = sprite->height / 2;
	wall_diff_height_std = plane_height_std / 2;	
	height_floor = doom->lib.sector[sprite->sector].height_floor / sprite->distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + wall_diff_height_std) - doom->own_event.y_pitch - height_floor;
	sprite_end->y = sidedef_bottom;
	sprite_begin->y = sprite_end->y - sprite->height;
	if (sprite_begin->y < 0)
		sprite_begin->y = 0;
	if (sprite_end->y > HEIGHT)
		sprite_end->y = HEIGHT - 1;
	h = doom->lib.obj_lib[sprite->index]->h;
	w = doom->lib.obj_lib[sprite->index]->w;
	sprite->width = (sprite->height / h) * w;
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
	while (i < doom->visible_sprites)
	{
		index = sprite_order[i];
		scale_sprite(doom, &sprite_begin, &sprite_end, &doom->lib.sprites[index]);
		draw_stripes(doom, &sprite_begin, &sprite_end, index);
		doom->lib.sprites[index].visible = 0;
		i++;
	}
	doom->visible_sprites = 0;
}

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	sprite_order = sort_sprite_array(doom->lib.sprites, doom->visible_sprites);
	draw_sprite(doom, sprite_order);
	//free sprite order
}

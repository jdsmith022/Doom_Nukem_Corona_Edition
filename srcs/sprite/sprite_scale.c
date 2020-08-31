/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_scale.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:53:57 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/31 17:34:19 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

int			find_virus_bottom(t_doom *doom, t_sprite *sprite,\
			int virus_bottom, int virus_top)
{
	int		height_space_part;
	int		diff;
	int		move;
	int		val;

	val = doom->lib.sprite_height[doom->lib.move];
	height_space_part = (virus_bottom - virus_top) / 5;
	if (sprite->index % 3 == 0)
		virus_bottom -= height_space_part;
	else if (sprite->index % 3 == 1)
		virus_bottom -= (height_space_part * 2);
	else
		virus_bottom -= (height_space_part * 3);
	virus_bottom = virus_move(virus_bottom, height_space_part,\
		val, sprite->index);
	return (virus_bottom);
}

int		calculate_sprite_bottom(t_doom *doom, t_sprite *sprite,\
			double scale)
{
	int			sidedef_bottom;
	double		height_floor;

	height_floor = doom->lib.sector[sprite->sector].height_floor\
		/ sprite->distance * doom->cast.dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + (doom->player.height * scale)) -\
		(doom->own_event.y_pitch + height_floor);
	return (sidedef_bottom);
}

int			calculate_sprite_top(t_doom *doom, t_sprite *sprite,\
			double scale)
{
	int			diff;
	double		height_ceiling;
	int			sidedef_top;

	diff = STD_TEXT_HEIGHT - doom->player.height;
	height_ceiling = doom->lib.sector[sprite->sector].height_ceiling\
		/ sprite->distance * doom->cast.dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - ((double)diff * scale)) -\
		(doom->own_event.y_pitch + height_ceiling);	
	return (sidedef_top);
}

double		sprite_calculations(t_doom *doom, t_sprite *sprite,\
			t_sector sector)
{
	int			sidedef_bottom;
	int			sidedef_top;
	int			plane_height_standard;
	double		scale;

	sprite->height = sprite->size / sprite->distance * doom->cast.dist_to_plane;
	plane_height_standard = doom->cast.texture_height / sprite->distance\
		* doom->cast.dist_to_plane;
	scale = (double)plane_height_standard / doom->cast.texture_height;
	sidedef_bottom = calculate_sprite_bottom(doom, sprite, scale);
	sidedef_top = calculate_sprite_top(doom, sprite, scale);
	if (sprite->action == 4 || sprite->action == 5)
		sidedef_bottom = find_virus_bottom(doom, sprite, sidedef_bottom,\
		sidedef_top);
	return (sidedef_bottom);
}

void		scale_sprite(t_doom *doom, t_line *coords,\
			t_sprite *sprite)
{
	double		h;
	double		w;
	int			width_left;
	int			width_right;

	coords->end.y = (double)sprite_calculations(doom, sprite,\
	doom->lib.sector[sprite->sector]);
	coords->start.y = coords->end.y - sprite->height;
	h = doom->lib.obj_lib[sprite->visible]->h;
	w = doom->lib.obj_lib[sprite->visible]->w;
	sprite->width = (sprite->height / h) * w;
	width_right = sprite->sprite_x / WIDTH * sprite->width;
	width_left = sprite->width - width_right;
	coords->end.x = sprite->sprite_x + width_right;
	coords->start.x = sprite->sprite_x - width_left;
	if (coords->start.x < 0)
		coords->start.x = 0;
	if (coords->end.x > WIDTH)
		coords->end.x = WIDTH - 1;
	sprite->sprite_begin.x = coords->start.x;
	sprite->sprite_begin.y = coords->start.y;
}

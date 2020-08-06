#include "../../includes/doom.h"

double		calculate_sprite_bottom(t_doom *doom, t_sprite *sprite)
{
	int			new_height;
	double		height_std;
	// int			div_height_std;
	double		height_floor;
	int			sidedef_bottom;
	// int			plane_height_std;
	int			wall_diff_height_std;

	new_height = (HEIGHT / 2) + doom->player_height;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	// plane_height_std = doom->texture_height / sprite->distance * doom->dist_to_plane;
	// div_height_std = plane_height_std / 2 ;
	wall_diff_height_std = (doom->texture_height / sprite->distance\
		* doom->dist_to_plane) / 2;
	height_floor = doom->lib.sector[sprite->sector].height_floor\
		/ sprite->distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + wall_diff_height_std) -\
		doom->own_event.y_pitch - height_floor;
	return (sidedef_bottom);
}

void		scale_sprite(t_doom *doom, t_point *sprite_begin,\
			t_point *sprite_end, t_sprite *sprite)
{
	double		h;
	double		w;
	int			width_left;
	int			width_right;

	sprite_end->y = (double)calculate_sprite_bottom(doom, sprite);
	sprite_begin->y = sprite_end->y - sprite->height;
	if (sprite_begin->y < 0)
		sprite_begin->y = 0;
	if (sprite_end->y > HEIGHT)
		sprite_end->y = HEIGHT - 1;
	h = doom->lib.obj_lib[sprite->visible]->h;
	w = doom->lib.obj_lib[sprite->visible]->w;
	sprite->width = (sprite->height / h) * w;
	width_right = sprite->sprite_x / WIDTH * sprite->width;
	width_left = sprite->width - width_right;
	sprite_end->x = sprite->sprite_x + width_right;
	sprite_begin->x = sprite->sprite_x - width_left;
	if (sprite_begin->x < 0)
		sprite_begin->x = 0;
	if (sprite_end->x > WIDTH)
		sprite_end->x = WIDTH - 1;
}

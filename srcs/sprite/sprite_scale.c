#include "../../includes/doom.h"

//calculate offset??
void		scale_sprite(t_doom *doom, t_point *sprite_begin, t_point *sprite_end,\
t_sprite *sprite, int index)
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
	int			width_left; //try-out
	int			width_right; //try-out

	new_height = (HEIGHT / 2) + doom->player_height;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	plane_height_std = doom->texture_height / sprite->distance * doom->dist_to_plane;
	// div_height_std = sprite->height / 2;
	div_height_std = plane_height_std / 2 ;
	wall_diff_height_std = plane_height_std / 2;	
	height_floor = doom->lib.sector[sprite->sector].height_floor / sprite->distance * doom->dist_to_plane;
	sidedef_bottom = (new_height + wall_diff_height_std) - doom->own_event.y_pitch - height_floor;
	sprite_end->y = sidedef_bottom;
	sprite_begin->y = sprite_end->y - sprite->height;
	if (sprite_begin->y < 0)
		sprite_begin->y = 0;
	if (sprite_end->y > HEIGHT)
		sprite_end->y = HEIGHT - 1;
	// h = doom->lib.obj_lib[sprite->index]->h;
	// w = doom->lib.obj_lib[sprite->index]->w;
	h = doom->lib.obj_lib[sprite->visible]->h;
	w = doom->lib.obj_lib[sprite->visible]->w;
	sprite->width = (sprite->height / h) * w;	
	// printf("scale_sprite #%d\ttex_h: %f\ttex_w: %f\nscreen_h: %f\tscreen_w: %f\n", index, h, w, sprite->height, sprite->width);
	
	//try-out
	width_right = sprite->sprite_x / WIDTH * sprite->width;
	width_left = sprite->width - width_right;
	sprite_end->x = sprite->sprite_x + width_right;
	sprite_begin->x = sprite->sprite_x - width_left;
	//end try-out
	
	
	
	
	// sprite_end->x = sprite->sprite_x; //outcommented because of try-out
	// sprite_begin->x = sprite_end->x - sprite->width; //outcommendted because of try-out
	if (sprite_begin->x < 0)
		sprite_begin->x = 0;
	if (sprite_end->x > WIDTH)
		sprite_end->x = WIDTH - 1;
}

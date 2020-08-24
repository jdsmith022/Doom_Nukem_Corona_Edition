#include "../../includes/doom.h"
#include "../../includes/sprites.h"

int			find_virus_bottom(t_doom *doom, t_sprite *sprite,\
			int virus_bottom, int virus_top)
{
	int		height_space_part;

	height_space_part = (virus_bottom - virus_top) / 5;
	if (sprite->index % 3 == 0)
		virus_bottom -= height_space_part;
	else if (sprite->index % 3 == 1)
		virus_bottom -= (height_space_part * 2);
	else
		virus_bottom -= (height_space_part * 3);
	return (virus_bottom);
}

double		calculate_sprite_bottom(t_doom *doom, t_sprite *sprite,\
			t_sector sector)
{
	double		height_floor;
	double		height_ceiling;
	int			sidedef_bottom;
	int			sidedef_top;
	int			sector_floor;
	int			plane_height_standard;
	double		scale;
	int			diff;

	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	plane_height_standard = doom->texture_height / sprite->distance\
		* doom->dist_to_plane;
	scale = (double)plane_height_standard / doom->texture_height;
	height_floor = doom->lib.sector[sprite->sector].height_floor\
		/ sprite->distance * doom->dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + (doom->player_height * scale)) -\
		(doom->own_event.y_pitch + height_floor);
	diff = STD_TEXT_HEIGHT - doom->player_height;
	height_ceiling = doom->lib.sector[sprite->sector].height_ceiling\
		/ sprite->distance * doom->dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - ((double)diff * scale)) -\
		(doom->own_event.y_pitch + height_ceiling);
	//this can go into a seperate function, take pointer of sidedef_bottom
	//find_virus_bottom(doom, sprite, &sidedef_bottom, sidedef_top)
	if (sprite->action == 4 || sprite->action == 5)
		sidedef_bottom = find_virus_bottom(doom, sprite, sidedef_bottom,\
		sidedef_top);
	//until here
	return (sidedef_bottom);
}

void		scale_sprite(t_doom *doom, t_point *sprite_begin,\
			t_point *sprite_end, t_sprite *sprite)
{
	double		h;
	double		w;
	int			width_left;
	int			width_right;

	sprite_end->y = (double)calculate_sprite_bottom(doom, sprite,\
	doom->lib.sector[sprite->sector]);
	sprite_begin->y = sprite_end->y - sprite->height;
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
	sprite->sprite_begin.x = sprite_begin->x;
	sprite->sprite_begin.y = sprite_begin->y;
}

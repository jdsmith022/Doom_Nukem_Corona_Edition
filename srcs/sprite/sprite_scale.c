#include "../../includes/doom.h"

int			find_virus_bottom(t_doom *doom, t_sprite *sprite, int virus_bottom, int virus_top)
{
	int		height_space_part;

	height_space_part = (virus_bottom - virus_top) / 5;
	if (sprite->index % 3 == 0)
	{
		virus_bottom -= height_space_part;
	}
	else if (sprite->index % 3 == 1)
	{
		virus_bottom -= (height_space_part * 2);
	}
	else
	{
		virus_bottom -= (height_space_part * 3);
	}
	return (virus_bottom);
}

double		calculate_sprite_bottom(t_doom *doom, t_sprite *sprite, t_sector sector)
{
	// int			new_height;
	// double		height_std;
	// int			div_height_std;
	double		height_floor;
	double		height_ceiling;
	int			sidedef_bottom;
	int			sidedef_top;
	int			sector_floor;
	// int			wall_diff_height_std;
	int			plane_height_standard;
	double		scale;
	int			diff;

	// new_height = (HEIGHT / 2) + doom->player_height;
	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
	plane_height_standard = doom->texture_height / sprite->distance\
		* doom->dist_to_plane;
	// scale = sprite->size / doom->lib.obj_lib[sprite->index]->h;
	scale = (double)plane_height_standard / doom->texture_height;
	// scale = plane_height_standard / doom->texture_height;
	//bovenstaande is wel echt de te verwachte hoogte van de sprite
	// div_height_std = plane_height_std / 2 ;

	//START SIDEDEF_BOTTOM

	// wall_diff_height_std = (doom->texture_height / sprite->distance\
		// * doom->dist_to_plane) / 2;
	height_floor = doom->lib.sector[sprite->sector].height_floor\
		/ sprite->distance * doom->dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + (doom->player_height * scale)) -\
		(doom->own_event.y_pitch + height_floor);
	// if (sidedef_bottom < 0)
	// 	sidedef_bottom = 0;
	// else if (sidedef_bottom > HEIGHT)
	// 	sidedef_bottom = HEIGHT;
	// return (sidedef_bottom);
	
	//START SIDEDEF _TOP
	diff = STD_TEXT - doom->player_height;
	height_ceiling = doom->lib.sector[sprite->sector].height_ceiling\
		/ sprite->distance * doom->dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - ((double)diff * scale)) -\
		(doom->own_event.y_pitch + height_ceiling);


	// sidedef_top = (new_height - (plane_height_standard / 2)) \
	// 	- doom->own_event.y_pitch - height_floor;

	// PLAATS VIRUS RANDOMLY
	if (sprite->action == 4 || sprite->action == 5)
		sidedef_bottom = find_virus_bottom(doom, sprite, sidedef_bottom,\
		sidedef_top);
	return (sidedef_bottom);
}

// double		calculate_sprite_bottom(t_doom *doom, t_sprite *sprite)
// {
// 	int			new_height;
// 	double		height_std;
// 	// int			div_height_std;
// 	double		height_floor;
// 	double		height_ceiling;
// 	int			sidedef_bottom;
// 	int			sidedef_top;
// 	int			wall_diff_height_std;
// 	int			plane_height_standard;

// 	new_height = (HEIGHT / 2) + doom->player_height;
// 	plane_height_standard = doom->texture_height / sprite->distance\
// 		* doom->dist_to_plane;
// 	sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;
// 	// div_height_std = plane_height_std / 2 ;
// 	wall_diff_height_std = (doom->texture_height / sprite->distance\
// 		* doom->dist_to_plane) / 2;
// 	height_floor = doom->lib.sector[sprite->sector].height_floor\
// 		/ sprite->distance * doom->dist_to_plane;
// 	sidedef_bottom = (new_height + wall_diff_height_std) -\
// 		doom->own_event.y_pitch - height_floor;
// 	sidedef_top = (new_height - (plane_height_standard / 2)) \
// 		- doom->own_event.y_pitch - height_floor;
// 	if (sprite->action == 4 || sprite->action == 5)
// 		sidedef_bottom = find_virus_bottom(doom, sprite, sidedef_bottom,\
// 		sidedef_top);
// 	return (sidedef_bottom);


	// int			diff;


	// diff = doom->texture_height - doom->player_height;

	// new_height = (HEIGHT / 2);
	// plane_height_standard = doom->texture_height / sprite->distance * doom->dist_to_plane;
	// double scale =  plane_height_standard / doom->texture_height;

	// sprite->height = sprite->size / sprite->distance * doom->dist_to_plane;

	// height_ceiling = doom->lib.sector[sprite->sector].height_ceiling / sprite->distance * doom->dist_to_plane;

	// sidedef_top = ((new_height) - (diff * scale)) - (doom->own_event.y_pitch - height_ceiling);

	// height_floor = doom->lib.sector[sprite->sector].height_floor / sprite->distance * doom->horizontal_plane_dist;
	// wall_diff_height_std = (doom->texture_height / sprite->distance\
	// 	* doom->dist_to_plane) / 2;

	// sidedef_bottom = ((new_height + wall_diff_height_std) + (doom->player_height * scale)) - (doom->own_event.y_pitch - height_floor);
	// return (sidedef_bottom);
// }

void		offset_sprite(t_doom *doom, t_point *sprite_begin,\
			t_point *sprite_end, t_sprite *sprite)
{
	int		size;
	int		size_left;
	int		size_right;
	int		width_left;
	int		width_right;

	if (sprite->action == 9 || sprite->action == 7)
		size = 20;
	else
		size = 10;
	printf("size: %d\n", size);
	printf("sprite_x: %f\n", sprite->sprite_x);
	if (sprite->offset_x < 0)
	{
		//middle is left
		printf("middle is left\n");
		size_left = (size / 2) + (sprite->offset_x * -1);
		size_right = size - size_left;
	}
	else if (sprite->offset_x > 0)
	{
		//middle is right
		printf("middle is right\n");
		size_right = (size / 2) + (sprite->offset_x);
		size_left = size - size_right;
	}
	else
	{
		//sprite_x is middle, width_right and width_left are equal
		printf("middle is middle\n");
		size_right = size / 2;
		size_left = size / 2;
	}
	printf("size_left: %d, size_right: %d\n", size_left, size_right);
	width_left = ((double)size_left / size) * sprite->width;
	width_right = ((double)size_right / size) * sprite->width;
	printf("width: %f, width_left: %d, width_right: %d\n", sprite->width, width_left, width_right);
	sprite_end->x = sprite->sprite_x + width_right;
	sprite_begin->x = sprite->sprite_x - width_left;
	printf("begin_x: %f, end_x: %f\n", sprite_begin->x, sprite_end->x);
	if (sprite_begin->x < 0)
		sprite_begin->x = 0;
	if (sprite_end->x > WIDTH)
		sprite_end->x = WIDTH - 1;
	sprite->sprite_begin.x = sprite_begin->x;
	sprite->sprite_begin.y = sprite_begin->y;
	printf("begin_x: %f, end_x: %f\n", sprite->sprite_begin.x, sprite_end->x);
}

void		scale_sprite(t_doom *doom, t_point *sprite_begin,\
			t_point *sprite_end, t_sprite *sprite)
{
	double		h;
	double		w;
	int			width_left;
	int			width_right;

	sprite_end->y = (double)calculate_sprite_bottom(doom, sprite, doom->lib.sector[sprite->sector]);
	sprite_begin->y = sprite_end->y - sprite->height;
	// sprite_begin->y and sprite_end->y should stay the same, even when it's less than zero
	h = doom->lib.obj_lib[sprite->visible]->h;
	w = doom->lib.obj_lib[sprite->visible]->w;
	sprite->width = (sprite->height / h) * w;
	printf("begin offset sprite\n");
	offset_sprite(doom, sprite_begin, sprite_end, sprite);
	printf("end offset sprite\n");

	// width_right = sprite->sprite_x / WIDTH * sprite->width;
	// width_left = sprite->width - width_right;
	// sprite_end->x = sprite->sprite_x + width_right;
	// sprite_begin->x = sprite->sprite_x - width_left;
	// if (sprite_begin->x < 0)
	// 	sprite_begin->x = 0;
	// if (sprite_end->x > WIDTH)
	// 	sprite_end->x = WIDTH - 1;
	// sprite->sprite_begin.x = sprite_begin->x;
	// sprite->sprite_begin.y = sprite_begin->y;
}

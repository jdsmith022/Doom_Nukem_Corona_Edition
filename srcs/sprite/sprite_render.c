#include "../../includes/doom.h"

void		scale_sprite(t_doom *doom, t_sprite *sprite)
{
	double		h;
	double		w;

	// h = doom->lib.obj_lib[sprite->index]->h;
	// w = doom->lib.obj_lib[sprite->index]->w;
	h = 64;
	w = 64;
	sprite->height = (sprite->size / sprite->distance * doom->dist_to_plane);
	sprite->width = (sprite->size / sprite->distance * doom->dist_to_plane);
	// (sprite->height / h) * w;
}

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;
	t_point sprite_cord;

	i = 0;
	printf("draw_sprite %d\n", doom->visible_sprites);
	while (i < doom->visible_sprites)
	{
		printf("*index: %d\n", sprite_order[i]);
		index = sprite_order[i];
		//scale sprites
		scale_sprite(doom, &doom->lib.sprites[index]);
		printf("height: %f\nwidth: %f\n", doom->lib.sprites[index].height, doom->lib.sprites[index].width);

		//find position on screen
		find_position(doom, &sprite_cord, index);
			//sector portals (niet vergeten, niet opslaan als een muur)
			//in sidedef render opslaan
			//set_wall_properties (plane_projections)
		draw_stripes(doom, sprite_cord, index);
		// turn visibility off
		doom->lib.sprites[index].visible = 0;
		i++;
	}
	doom->visible_sprites = 0;
}

void		sprite_render(t_doom *doom)
{
	int		*sprite_order;

	printf("sprite_render 1\n");
	//sort sprite array
	// printf("visible sprites: %d\n", doom->visible_sprites);
	sprite_order = sort_sprite_array(doom->lib.sprites, doom->visible_sprites);

	printf("sprite_render 2\n");
	//draw sprites
	draw_sprite(doom, sprite_order);
	//(scale sprite and find_position))
		//turn visibility off
		//set doom->visible_sprite to 0
		//free sprite_order
}

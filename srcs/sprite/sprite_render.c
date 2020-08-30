#include "../../includes/doom.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

void		find_prev_sectors(t_doom *doom, t_sprite *sprite)
{
	t_line		sprite_ray;

	sprite->n_sector = 0;
	find_sidedef_intersect_per_sector(doom, sprite,\
	doom->i_sector, doom->i_sector);
}

void		draw_sprite(t_doom *doom, int *sprite_order)
{
	int		i;
	int		index;
	t_line	sprite;

	i = 0;
	while (i < doom->visible_sprites)
	{
		index = sprite_order[i];
		if (doom->i_sector != doom->lib.sprites[index].sector)
			find_prev_sectors(doom, &doom->lib.sprites[index]);
		if (doom->own_event.window == TRUE)
		{
			if (doom->lib.sprites[index].sector ==\
			doom->lib.window.curr_sector)
				draw_window_as_sprite(doom);
		}
		scale_sprite(doom, &sprite, &doom->lib.sprites[index]);
		draw_stripes(doom, &sprite, index);
		i++;
	}
	if (doom->own_event.window == TRUE)
		draw_window_as_sprite(doom);
}

void		sprite_render(t_doom *doom)
{
	if (doom->lib.move < 19)
		doom->lib.move++;
	else
		doom->lib.move = 0;
	if (doom->lib.sprite_order != NULL)
	{
		ft_bzero(doom->lib.sprite_order, doom->visible_sprites);
		free(doom->lib.sprite_order);
	}
	doom->lib.sprite_order = sort_sprite_array(doom->lib.sprites,\
	doom->visible_sprites, doom->total_sprites);
	if (doom->own_event.window == TRUE)
		sort_sprites_window(doom->lib.sprite_order, doom->i_sector,\
		doom->visible_sprites, doom->lib.sprites);
	draw_sprite(doom, doom->lib.sprite_order);
}

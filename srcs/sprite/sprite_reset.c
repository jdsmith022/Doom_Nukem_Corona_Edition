#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		sprite_reset(t_doom *doom)
{
	int		i;

	i = 0;
	while (i < doom->total_sprites)
	{
		doom->lib.sprites[i].visible = -1;
		doom->lib.sprites[i].n_sector = 0;
		//free sprite_order_array???
		i++;
	}
}

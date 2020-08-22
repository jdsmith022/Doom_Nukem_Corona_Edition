#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		sprite_reset(t_doom *doom)
{
	int		i;

	i = 0;
	while (i < doom->total_sprites)
	{
		doom->lib.sprites[i].visible = -1;
		// ft_bzero(doom->lib.sprites[i].prev_sectors, doom->lib.sprites[i].n_sector);
		doom->lib.sprites[i].n_sector = 0;
		//free prev_sectors???
		i++;
	}
}

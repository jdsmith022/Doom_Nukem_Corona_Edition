#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

t_sector	*light_correction(t_sector *sector, int len)
{
	int i;

	i = 0;
	while (i <= len)
	{
		if (sector[i].light_level != 0)
			sector[i].light_level /= 10.0;
		sector[i].light = TRUE;
		i++;
	}
	return (sector);
}

void		rmove(t_sprite *sprite, t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->total_sprites)
	{
		free(sprite[i].lines);
		free(sprite[i].textures);
		i++;
	}
	free(sprite);
}

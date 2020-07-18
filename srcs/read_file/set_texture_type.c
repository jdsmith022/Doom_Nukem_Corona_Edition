#include "../../includes/doom.h"

void	set_texture_type(const char *name, SDL_Surface *surface)
{
	uint8_t i;

	i = 0;
	surface->userdata = ft_memalloc(sizeof(uint8_t));
	while (i < GROCERY_LENGTH)
	{
		if (!ft_strcmp(name, grocerie_paths[i].path_shelf) ||
			!ft_strcmp(name, grocerie_paths[i].path_sprite))
		{
			memcpy(surface->userdata, &grocerie_paths[i].type, sizeof(uint8_t));
			break ;
		}
		i++;
	}
	return ;
}

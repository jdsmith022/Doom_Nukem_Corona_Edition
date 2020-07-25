#include "../../includes/doom.h"
#include "../../includes/textures.h"

static bool	is_of_type(const char *path_loaded, t_grocery_paths path)
{
	if (!ft_strcmp(path_loaded, path.path_shelf))
		return true;
	else if (!ft_strcmp(path_loaded, path.path_sprite))
		return true;
	else
		return false;
}

void		set_texture_type(const char *name, SDL_Surface *surface)
{
	uint8_t	i;

	i = 0;
	surface->userdata = ft_memalloc(sizeof(uint8_t)); // NOTE: FREE
	ft_bzero(surface->userdata, sizeof(uint8_t));
	while (i < NUM_OF_GROCERIES)
	{
		if (is_of_type(name, GROCERIE_PATHS[i]))
		{
			memcpy(surface->userdata, &GROCERIE_PATHS[i].type, sizeof(uint8_t));
			break ;
		}
		i++;
	}
	return ;
}

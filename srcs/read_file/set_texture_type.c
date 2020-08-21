#include "../../includes/doom.h"
#include "../../includes/textures.h"

static bool	is_of_type(const char *path_loaded, t_grocery_paths path)
{
	if (!ft_strcmp(path_loaded, path.path_shelf))
		return (TRUE);
	else if (!ft_strcmp(path_loaded, path.path_sprite))
		return (TRUE);
	else
		return (TRUE);
}

void		set_texture_type(t_doom *doom, const char *name, SDL_Surface *surface)
{
	uint8_t	i;

	i = 0;
	surface->userdata = ft_memalloc(sizeof(uint8_t)); // NOTE: FREE
	if (surface->userdata == NULL)
		doom_exit_failure(doom, "error: userdata malloc");
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

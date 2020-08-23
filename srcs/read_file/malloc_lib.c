#include "../../includes/doom.h"
#include "../../includes/read.h"

t_bmp			*malloc_images_lib(t_doom *doom, int len)
{
	t_bmp *temp_images;

	temp_images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (temp_images == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (temp_images);
}

SDL_Surface		**malloc_sdl_lib(t_doom *doom, t_bmp *images, int len)
{
	SDL_Surface **temp_lib;

	temp_lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (temp_lib == NULL)
	{
		doom_exit_lib_failure(images, MALLOC_ERR);
		doom_exit_failure(doom, MALLOC_ERR);
	}
	return (temp_lib);
}

#include "../../includes/doom.h"

t_tga		*malloc_tga(t_doom *doom, int len)
{
	t_tga *temp_tga;

	temp_tga = (t_tga *)ft_memalloc(sizeof(t_tga) * len);
	if (temp_tga == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (temp_tga);
}

t_bmp			*malloc_bmp(t_doom *doom, int len)
{
	t_bmp *temp_bmp;

	temp_bmp = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (temp_bmp == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	return (temp_bmp);
}

SDL_Surface		**malloc_sdl(t_doom *doom, void *images, int len)
{
	SDL_Surface **temp_sdl;

	temp_sdl = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (temp_sdl == NULL)
	{
		doom_exit_lib_failure(images, MALLOC_ERR);
		doom_exit_failure(doom, MALLOC_ERR);
	}
	return (temp_sdl);
}

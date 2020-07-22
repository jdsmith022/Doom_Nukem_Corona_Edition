#include "../../includes/doom.h"


void	tga_to_sdl(t_doom *doom, t_tga *tga, char *line)
{
	SDL_Surface **image;
	int 		len;

	len = doom->total_sprites;
	image = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (image == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
}

#include "../../includes/doom.h"

int		sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (1);
	doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (doom->window == NULL)
		return (1);
	doom->surface = SDL_GetWindowSurface(doom->window);
	if (doom->surface == NULL)
		return (1);
	SDL_WarpMouseInWindow(doom->window, WIDTH / 2, HEIGHT / 2);
	return (0);
}

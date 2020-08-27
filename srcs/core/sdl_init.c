
#include "../../includes/doom.h"

void		sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		doom_exit_failure(doom, "unable to initialize SDL\n");
	doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (doom->window == NULL)
		doom_exit_failure(doom, "unable to initialize SDL\n");
	doom->surface = SDL_GetWindowSurface(doom->window);
	if (doom->surface == NULL)
		doom_exit_failure(doom, "unable to initialize SDL\n");
}

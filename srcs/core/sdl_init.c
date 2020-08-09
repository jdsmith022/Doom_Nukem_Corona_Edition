#include "../../includes/doom.h"

int		sdl_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) // check what to init
		return (1);
	doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	// doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	// SDL_GetWindowSize(doom->window, &doom->win_h, &doom->wind_w);
	// printf("doom: %d, %d\n", HEIGHT, WIDTH);
	// SDL_SetWindowInputFocus(doom->window);
	if (doom->window == NULL)
		return (1);
	doom->surface = SDL_GetWindowSurface(doom->window);
	if (doom->surface == NULL)
		return (1);
	SDL_WarpMouseInWindow(doom->window, WIDTH / 2, HEIGHT / 2);
	// SDL_CaptureMouse(SDL_TRUE);
	return (0);
}

#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void	mouse_handler(t_doom *doom, SDL_MouseButtonEvent *button)
{
	// int x;
	// int y;

	// x = doom->own_event.hold_x;
	// y = doom->own_event.hold_y;
	// if (x >= && x <= && y >= && y <= )
	// 	doom->menu->start = TRUE;
	// if (x >= && x <= && y >= && y <= )
	// 	doom->menu->game_editor = TRUE;
	// if (x >= && x <= && y >= && y <= )
	// 	doom->menu->settings = TRUE;
}

void	mouse_settings(t_doom *doom, double dt)
{
	SDL_Event event;

	event = doom->event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom_exit_success(doom);
		if (event.type == SDL_KEYDOWN)
			if (event.key.keysym.sym == SDLK_ESCAPE)
				doom_exit_success(doom);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(doom, &event.button, doom->own_event);
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(doom, &event.button);
	}
	mouse_handler(doom, &event.button);
}

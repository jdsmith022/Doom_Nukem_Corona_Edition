#include "../../includes/doom.h"
#include "../../includes/action.h"

void	doom_update(t_doom *doom, double dt)
{
	SDL_Event event;

	event = doom->event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom->is_running = FALSE;
		if (event.type == SDL_KEYDOWN)
			key_press(doom, &doom->own_event, &event.key);
		if (event.type == SDL_KEYUP)
			key_release(&doom->own_event, &event.key);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(doom, &event.button, doom->own_event);
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(doom, &event.button);
		if (event.type == SDL_MOUSEMOTION && doom->own_event.fall == FALSE)
			move_cam_direction(doom, &event.motion, dt, &doom->own_event);
	}
	key_handler(doom, &doom->own_event, dt);
	if (doom->game_editor == FALSE)
		action_handler(doom);
	// printf("end doom update\n");
}

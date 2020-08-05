#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void		mouse_handeler2(t_doom *doom, SDL_MouseButtonEvent *button)
{
	int			x;
	int			y;
	SDL_Rect	rect;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	rect = doom->lib.font_lib.setting_menu_font[8].font_rect;
	if (doom->menu->settings == TRUE && \
	x >= (rect.x) && x <= (rect.x + 200) && \
	y >= (rect.y) && y <= (rect.y + 25))
		doom->menu->settings = FALSE;
}

static void		mouse_handler(t_doom *doom, SDL_MouseButtonEvent *button)
{
	int			x;
	int			y;
	SDL_Rect	rect1;
	SDL_Rect	rect2;
	SDL_Rect	rect3;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	rect1 = doom->lib.font_lib.start_menu_font[2].font_rect;
	rect2 = doom->lib.font_lib.start_menu_font[3].font_rect;
	rect3 = doom->lib.font_lib.start_menu_font[4].font_rect;
	if (x >= (rect1.x) && x <= (rect1.x + 200) && \
	y >= (rect1.y) && y <= (rect1.y + 25))
	{
		doom->is_running = TRUE;
		doom->menu->menu = FALSE;
	}
	else if (x >= (rect2.x) && x <= (rect2.x + 200) && \
	y >= (rect2.y) && y <= (rect2.y + 25))
		doom->menu->settings = TRUE;
	else if (x >= (rect3.x) && x <= (rect3.x + 200) && \
	y >= (rect3.y) && y <= (rect3.y + 25))
	{
		doom->is_running = TRUE;
		doom->game_editor = TRUE;
		doom->menu->menu = FALSE;
	}
	mouse_handeler2(doom, button);
}

void		mouse_settings(t_doom *doom, double dt)
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

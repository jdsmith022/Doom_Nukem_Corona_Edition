#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void		setting_menu_click_event(t_doom *doom, SDL_Rect rect)
{
	int			x;
	int			y;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	if (x >= (rect.x) && x <= (rect.x + 200) && \
	y >= (rect.y) && y <= (rect.y + 25))
		doom->menu->settings = FALSE;
	doom->own_event.hold_x = 0;
	doom->own_event.hold_y = 0;
}

static void		start_menu_click_event(t_doom *doom, SDL_Rect rect1,
					SDL_Rect rect2, SDL_Rect rect3)
{
	int			x;
	int			y;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
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
}

static void		mouse_handler(t_doom *doom)
{
	SDL_Rect	rect1;
	SDL_Rect	rect2;
	SDL_Rect	rect3;

	if (doom->menu->settings == FALSE)
	{
		rect1 = doom->lib.font_lib.start_menu_font[2].font_rect;
		rect2 = doom->lib.font_lib.start_menu_font[3].font_rect;
		rect3 = doom->lib.font_lib.start_menu_font[4].font_rect;
		start_menu_click_event(doom, rect1, rect2, rect3);
	}
	else
	{
		rect1 = doom->lib.font_lib.setting_menu_font[9].font_rect;
		setting_menu_click_event(doom, rect1);
	}
}

void			mouse_settings(t_doom *doom)
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
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				doom->own_event.hold_x = event.button.x;
				doom->own_event.hold_y = event.button.y;
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN || \
	event.type == SDL_MOUSEBUTTONUP)
		mouse_handler(doom);
}

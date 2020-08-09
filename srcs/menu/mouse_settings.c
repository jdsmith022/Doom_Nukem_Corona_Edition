#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void		setting_game_over_click_event(t_doom *doom, SDL_Rect rect)
{
	int			x;
	int			y;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	if (x >= (rect.x) && x <= (rect.x + 200) && \
	y >= (rect.y) && y <= (rect.y + 25))
	{
		doom->menu->retry = TRUE;
		doom->start = FALSE;
		doom_retry(doom);
		game_init(doom);
	}
}

static void		setting_menu_click_event(t_doom *doom, SDL_Rect rect)
{
	int			x;
	int			y;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	if (x >= (rect.x) && x <= (rect.x + 200) && \
	y >= (rect.y) && y <= (rect.y + 25))
		doom->menu->settings = FALSE;
}

static void		difficulty_setting(t_doom *doom, int x, int y)
{
	if (x >= 430 && x <= 450 && y >= 300 && y <= 330)
		doom->difficulty = 1;
	else if (x >= 475 && x <= 500 && y >= 300 && y <= 330)
		doom->difficulty = 2;
	else if (x >= 530 && x <= 550 && y >= 300 && y <= 330)
		doom->difficulty = 3;
	doom->menu->menu = FALSE;
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
		doom->game_editor = TRUE;
		doom->menu->menu = FALSE;
	}
	else if (x >= 425 && x <= 560 && y >= 300 && y <= 330)
		difficulty_setting(doom, x, y);
}

static void		mouse_handler(t_doom *doom)
{
	SDL_Rect	rect1;
	SDL_Rect	rect2;
	SDL_Rect	rect3;

	if (doom->menu->settings == TRUE)
	{
		rect1 = doom->lib.font_lib.setting_menu_font[9].font_rect;
		setting_menu_click_event(doom, rect1);
	}
	else if (doom->menu->menu == TRUE)
	{
		rect1 = doom->lib.font_lib.start_menu_font[2].font_rect;
		rect2 = doom->lib.font_lib.start_menu_font[4].font_rect;
		rect3 = doom->lib.font_lib.start_menu_font[5].font_rect;
		start_menu_click_event(doom, rect1, rect2, rect3);
	}
	else if (doom->menu->game_over == TRUE)
	{
		rect1 = doom->lib.font_lib.game_over_font[2].font_rect;
		setting_game_over_click_event(doom, rect1);
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

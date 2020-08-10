#include "../../includes/doom.h"
#include "../../includes/menu.h"

void		pause_click_event(t_doom *doom, SDL_Rect rect)
{
	int			x;
	int			y;

	x = doom->own_event.hold_x;
	y = doom->own_event.hold_y;
	if (x >= (rect.x) && x <= (rect.x + 200) && \
	y >= (rect.y) && y <= (rect.y + 25))
		doom->menu->pause = FALSE;
}

void		setting_menu_click_event(t_doom *doom, SDL_Rect rect)
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

void		start_menu_click_event(t_doom *doom, SDL_Rect rect1,
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

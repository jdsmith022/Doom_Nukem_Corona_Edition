#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

void	mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.mouse_press = FALSE;
	}
}

void	mouse_press(t_doom *doom, SDL_MouseButtonEvent *button, t_event event)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = button->x;
		doom->own_event.hold_y = button->y;
		doom->own_event.mouse_press = TRUE;
		if (doom->own_event.shoot == TRUE)
		{
			if (doom->hud->sanitizer_level > 0)
			{
				doom->hud->sanitizer_shooting = TRUE;
				doom->own_event.mist = TRUE;
				shooting(doom);
			}
		}
	}
	if (doom->game_editor == TRUE)
		mouse_press_game_editor(doom, button->x, button->y);
}

bool	handle_mouse_state(t_doom *doom)
{
	if (doom->own_event.mouse_state_switched)
		return (FALSE);
	doom->own_event.mouse_state_switched = TRUE;
	return (TRUE);
}

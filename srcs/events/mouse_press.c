#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/action.h"

void	mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
		doom->own_event.mouse_press = FALSE;
}

void	mouse_press(t_doom *doom, SDL_MouseButtonEvent *button, t_event event)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = button->x;
		doom->own_event.hold_y = button->y;
		doom->own_event.mouse_press = TRUE;
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

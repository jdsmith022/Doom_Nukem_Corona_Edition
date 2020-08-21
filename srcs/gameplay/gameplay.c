#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void				groceries(t_doom *doom)
{
	if (!doom->own_event.shoot && !doom->own_event.select){
		if (MOUSE_PRESSED)
			handle_groceries(doom);
		else
			doom->own_event.mouse_state_switched = false;
	}
}

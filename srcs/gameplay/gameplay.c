#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void				groceries(t_doom *doom)
{
	if (doom->own_event.select || doom->own_event.mouse_pointer)
	{
		if (doom->own_event.mouse_press)
			handle_groceries(doom);
		else
			doom->own_event.mouse_state_switched = FALSE;
	}	
}

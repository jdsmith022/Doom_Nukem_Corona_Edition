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
	if (doom->groceries->basket)
		draw_basket_ui(doom, doom->groceries);
	if (doom->groceries->shopping_list)
		draw_shopping_ui(doom, doom->groceries);
	if (SECTORS[doom->i_sector].action == EXIT_LEVEL)
	{
		get_game_over_info(doom);
		doom->menu->finished = TRUE;
	}
}

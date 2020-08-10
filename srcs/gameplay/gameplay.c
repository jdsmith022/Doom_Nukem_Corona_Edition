#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void			groceries(t_doom *doom)
{
	if (MOUSE_PRESSED)
		handle_groceries(doom);
	else
		doom->own_event.mouse_state_switched = false;
	if (doom->groceries->basket)
		draw_basket_ui(doom, doom->groceries);
	if (doom->groceries->shopping_list)
		draw_shopping_ui(doom, doom->groceries);
	if (SECTORS[doom->i_sector].action == 2){
		if (checkout(doom->groceries))
			printf("YEAH U WON!\n");
		else
			printf("srry u lost..\n");
		doom->menu->game_over = TRUE;
	}
}

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"

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
	// printf("i_sidef: %d\n", SECTORS[doom->i_sector].i_sidedefs);
	// printf("n_sidedef: %d\n", SECTORS[doom->i_sector].n_sidedefs);
	// if (SECTORS[doom->i_sector] == CHECKOUT)
	// 	checkout(doom->groceries);
}

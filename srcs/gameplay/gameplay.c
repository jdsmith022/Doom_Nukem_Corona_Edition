#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"

void				groceries(t_doom *doom)
{
	printf("sector: %d\n", SECTORS[doom->i_sector].action);
	if (doom->own_event.select == TRUE)
	{
		if (MOUSE_PRESSED)
			handle_groceries(doom);
		else
			doom->own_event.mouse_state_switched = false;
		if (doom->groceries->basket)
			draw_basket_ui(doom, doom->groceries);
		if (doom->groceries->shopping_list)
			draw_shopping_ui(doom, doom->groceries);
		if (SECTORS[doom->i_sector].action == EXIT_LEVEL)
		{
			printf("yo\n");
			get_game_over_info(doom);
			doom->menu->finished = TRUE;
		}
	}
}

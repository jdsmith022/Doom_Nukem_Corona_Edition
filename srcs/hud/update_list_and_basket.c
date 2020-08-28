
#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"

void	update_list_and_basket(t_doom *doom)
{
	if (doom->groceries->basket)
		draw_basket_ui(doom, doom->groceries);
	if (doom->groceries->shopping_list)
		draw_shopping_ui(doom, doom->groceries);
	if (doom->lib.sector[doom->i_sector].action == EXIT_LEVEL)
	{
		get_game_over_info(doom);
		doom->menu->state = finished;
	}
}

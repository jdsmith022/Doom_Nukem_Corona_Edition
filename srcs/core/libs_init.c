#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void		init_menu(t_doom *doom)
{
	doom->menu = (t_menu*)ft_memalloc(sizeof(t_menu));
	if (doom->menu == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->menu->start = FALSE;
	doom->menu->menu = TRUE;
	doom->menu->game_over = FALSE;
}

void		init_hud(t_doom *doom)
{
	doom->hud = (t_hud*)ft_memalloc(sizeof(t_hud));
	if (doom->hud == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->hud->corona = FALSE;
	doom->hud->sanitizer = FALSE;
	doom->hud->facemask = FALSE;
	doom->hud->health_pack = FALSE;
	doom->hud->health_pack_plus = FALSE;
	doom->hud->sanitizer_shooting = FALSE;
	doom->hud->shopper = FALSE;
	doom->hud->sanitizer_level = 100;
	doom->hud->corona_level = 0;
	doom->hud->hold_time = 360000;
	doom->hud->curr_time = 360000;
}

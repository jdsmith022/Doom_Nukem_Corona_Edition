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
	// doom->menu->menu = FALSE;
}

void		init_hud(t_doom *doom)
{
	int	time;

	time = 300;
	doom->hud = (t_hud*)ft_memalloc(sizeof(t_hud));
	if (doom->hud == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->hud->sanitizer_level = 100;
	doom->hud->corona_level = 0;
	time = time / doom->difficulty;
	doom->hud->time = time;
}

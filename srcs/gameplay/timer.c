#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void		timer(t_doom *doom)
{
	int diff;
	int	curr_time;

	if (doom->start_timer == TRUE)
	{
		doom->game_start_time = SDL_GetTicks();
		doom->start_timer = FALSE;
	}
	else
	{
		curr_time = SDL_GetTicks();
		diff = curr_time - doom->game_start_time;
		doom->hud->curr_time = doom->hud->hold_time - diff;
		doom->hud->curr_time /= 1000;
		if (doom->hud->curr_time == 0)
			doom->menu->game_over = TRUE;
	}
}

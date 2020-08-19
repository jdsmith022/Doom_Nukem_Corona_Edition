#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

static void	show_invisible_sprite(t_doom *doom)
{
	Uint32 index;

	index = 0;
	while (index < doom->total_sprites)
	{
		if (doom->lib.sprites[index].action == 8)
			doom->lib.sprites[index].action = 11;
		index++;
	}
}

void		timer(t_doom *doom)
{
	int diff;
	int	curr_time;

	if (doom->lib.sector[doom->i_sector].action == START_TIMER && \ 
	doom->menu->start_timer == FALSE)
	{
			doom->start_timer = TRUE;
			doom->menu->start_timer = TRUE;
			show_invisible_sprite(doom);
			doom->game_start_time = SDL_GetTicks();
	}
	else if (doom->menu->pause == FALSE && doom->game_editor == FALSE \
	&& doom->menu->start_timer == TRUE)
	{
		doom->start_timer = FALSE;
		curr_time = SDL_GetTicks();
		diff = curr_time - doom->game_start_time;
		doom->hud->curr_time = doom->hud->hold_time - diff;
		doom->hud->curr_time /= 1000;
		if (doom->hud->curr_time == 0)
			doom->menu->game_over = TRUE;
	}
}

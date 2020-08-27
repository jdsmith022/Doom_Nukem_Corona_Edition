
#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/font.h"
#include "../../includes/hud.h"
#include "../../includes/audio.h"

static void	set_menu_game_variables(t_doom *doom)
{
	doom->lib.font_lib.bools.walking_info = TRUE;
	doom->lib.font_lib.bools.walking_text = TRUE;
	doom->lib.font_lib.bools.start_sector = TRUE;
	doom->lib.font_lib.bools.trolly = FALSE;
	doom->lib.font_lib.bools.checkout = TRUE;
	doom->lib.font_lib.bools.scissor_lift = FALSE;
	doom->lib.font_lib.bools.text = FALSE;
	doom->own_event.select = FALSE;
	doom->start_timer = FALSE;
	doom->hud->hold_time /= doom->difficulty;
	doom->hud->curr_time /= doom->difficulty;
	doom->hud->update = list;
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void		doom_start(t_doom *doom)
{
	doom->difficulty = 1;
	while (doom->menu->state != start_game)
	{
		mouse_settings(doom);
		if (doom->menu->settings == FALSE)
			print_background(doom, 0x00002E);
		else
			print_background(doom, 0xF2F2F2);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
	Mix_HaltMusic();
	if (doom->game_editor == FALSE)
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
	set_menu_game_variables(doom);
}

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"

static void		finished_menu(t_doom *doom)
{
	add_score_to_sdl_text(doom);
	while (doom->menu->finished == TRUE)
		menu_print_loop(doom);
}

static void		game_over_menu(t_doom *doom)
{
	while (doom->menu->game_over == TRUE)
		menu_print_loop(doom);
}

static void		pause_menu(t_doom *doom)
{
	int hold_time;
	int curr_time;

	hold_time = SDL_GetTicks();
	while (doom->menu->pause == TRUE)
	{
		Mix_PauseMusic();
		menu_print_loop(doom);
	}
	doom->menu->pause = FALSE;
	resume_music();
	curr_time = SDL_GetTicks();
	doom->game_start_time = doom->game_start_time + (curr_time - hold_time);
	doom->hud_display = TRUE;
	SDL_SetRelativeMouseMode(TRUE);
}

void	menus(t_doom *doom)
{
	if (doom->menu->game_over == TRUE)
		game_over_menu(doom);
	if (doom->menu->pause == TRUE)
		pause_menu(doom);
	if (doom->menu->finished == TRUE)
		finished_menu(doom);
}

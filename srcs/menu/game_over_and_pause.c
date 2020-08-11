#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"
#include "../../includes/gameplay.h"

static void		menu_print_loop(t_doom *doom)
{
	doom->huds = FALSE;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	SDL_SetCursor(doom->cursor);
	mouse_settings(doom);
	print_background(doom, 0x00002E);
	font_to_screen(doom);
	SDL_UpdateWindowSurface(doom->window);
	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
}

static void		finished_menu(t_doom *doom)
{
	add_score_to_sdl_text(doom);
	while(doom->menu->finished == TRUE)
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
		menu_print_loop(doom);
	curr_time = SDL_GetTicks();
	doom->game_start_time = doom->game_start_time + (curr_time - hold_time);
	doom->huds = TRUE;
}

void	menus(t_doom* doom)
{
	if (doom->menu->game_over == TRUE)
		game_over_menu(doom);
	if (doom->menu->pause == TRUE)
		pause_menu(doom);
	if (doom->menu->finished == TRUE)
		finished_menu(doom);
}
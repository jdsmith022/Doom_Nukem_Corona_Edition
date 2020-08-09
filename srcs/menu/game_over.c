#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void	check_levels_and_time(t_doom *doom)
{
	if (doom->hud->corona_level >= 100)
		doom->menu->game_over = TRUE;
	while (doom->menu->game_over == TRUE || doom->hud->curr_time <= 0)
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
}

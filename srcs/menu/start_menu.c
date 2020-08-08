#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/font.h"

void		doom_start(t_doom *doom) // add difficulty
{
	while (doom->menu->menu == TRUE)
	{
		mouse_settings(doom);
		print_background(doom, 0x00002E);
		if (doom->menu->settings == TRUE)
			print_background(doom, 0xF2F2F2);
		font_to_screen(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	}
	doom->lib.font_lib.instruction = TRUE;
	doom->own_event.select = FALSE;
}

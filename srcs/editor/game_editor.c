#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

#include <stdio.h>

void	open_game_editor(t_doom *doom, double dt)
{
	Uint32				*pixels;
	int					i;

	ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
	while (doom->game.editor == TRUE)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		sdl_poll_events(doom, dt);
		doom->cast.distance = 1;
		pixels = doom->surface->pixels;
		if (doom->game_design.sector == NULL)
			init_game_design(doom);
		draw_screen_colors(pixels, doom);
		draw_images(pixels, doom);
		bars(&pixels, doom);
		i = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
		while (i < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs\
			+ doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
		{
			draw_lines(doom, &pixels, i);
			i++;
		}
		draw_object(doom, &pixels);
		draw_font(doom, doom->lib.font_lib.game_editor_font,\
			doom->lib.font_lib.ge_font_len);
		set_to_window(doom);
	}
}

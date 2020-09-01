#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

#include <stdio.h>

static void		set_draw_lines(t_doom *doom, Uint32 **pixels)
{
	t_ed_sidedef *ed_sidedef;

	ed_sidedef = doom->game_design.ed_sidedef;
	while (ed_sidedef)
	{
		draw_lines(doom, pixels, ed_sidedef);
		ed_sidedef = ed_sidedef->next;
	}
}

void	open_game_editor(t_doom *doom, double dt)
{
	Uint32				*pixels;
	t_ed_sidedef		*ed_sidedef;

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
		set_draw_lines(doom, &pixels);
		draw_object(doom, &pixels);
		draw_font(doom, doom->lib.font_lib.game_editor_font,\
			doom->lib.font_lib.ge_font_len);
		set_to_window(doom);
	}
}

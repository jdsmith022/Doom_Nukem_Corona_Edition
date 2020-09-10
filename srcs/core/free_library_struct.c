/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_library_struct.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 22:36:34 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

static void		free_sdl_surface(t_font *lib, uint8_t len)
{
	size_t index;

	index = 0;
	while (index < len)
	{
		SDL_FreeSurface(lib[index].font_surface);
		index++;
	}
}

static void		free_font_lib_2(t_doom *doom)
{
	if (doom->lib.font_lib.setting_menu_font)
	{
		free_sdl_surface(doom->lib.font_lib.setting_menu_font, \
			doom->lib.font_lib.setting_font_len);
		void_free_lib(doom->lib.font_lib.setting_menu_font);
	}
	if (doom->lib.font_lib.game_over_font)
	{
		free_sdl_surface(doom->lib.font_lib.game_over_font, \
			doom->lib.font_lib.game_font_len);
		void_free_lib(doom->lib.font_lib.game_over_font);
	}
	if (doom->lib.font_lib.instruction_font)
	{
		free_sdl_surface(doom->lib.font_lib.instruction_font, \
			doom->lib.font_lib.instruction_font_len);
		void_free_lib(doom->lib.font_lib.instruction_font);
	}
}

static void		free_font_lib(t_doom *doom)
{
	if (doom->lib.font_lib.game_editor_font)
	{
		free_sdl_surface(doom->lib.font_lib.game_editor_font, \
			doom->lib.font_lib.game_font_len);
		void_free_lib(doom->lib.font_lib.game_editor_font);
	}
	if (doom->lib.font_lib.hud_font)
	{
		free_sdl_surface(doom->lib.font_lib.hud_font, \
			doom->lib.font_lib.hud_font_len);
		void_free_lib(doom->lib.font_lib.hud_font);
	}
	if (doom->lib.font_lib.start_menu_font)
	{
		free_sdl_surface(doom->lib.font_lib.start_menu_font, \
			doom->lib.font_lib.start_font_len);
		void_free_lib(doom->lib.font_lib.start_menu_font);
	}
	free_font_lib_2(doom);
}

void			free_struct_lib(t_doom *doom)
{
	if (doom->lib.sector)
		void_free_lib(doom->lib.sector);
	if (doom->lib.sidedef)
		void_free_lib(doom->lib.sidedef);
	if (doom->lib.sprites)
		void_free_lib(doom->lib.sprites);
	if (doom->groceries)
		void_free_lib(doom->groceries);
	if (doom->hud)
		void_free_lib(doom->hud);
	if (doom->menu)
		void_free_lib(doom->menu);
	free_font_lib(doom);
}

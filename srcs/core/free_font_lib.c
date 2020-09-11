/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_font_lib.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/11 14:38:38 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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

void			free_font_lib(t_doom *doom)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:40:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/04 08:36:45 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_editor_text_3(t_doom *doom, t_font *lib)
{
	lib[10].str = "Select wall and";
	lib[10].font_rect.x = 645;
	lib[10].font_rect.y = 140;
	lib[10].font_color = doom->lib.font_lib.font_color.black;
}

static void	set_editor_text_2(t_doom *doom, t_font *lib)
{
	lib[5].str = "Light level";
	lib[5].font_rect.x = 25;
	lib[5].font_rect.y = 260;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "Select object";
	lib[6].font_rect.x = 22;
	lib[6].font_rect.y = 340;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "make it a portal";
	lib[7].font_rect.x = 645;
	lib[7].font_rect.y = 215;
	lib[7].font_color = doom->lib.font_lib.font_color.black;
	lib[8].str = "Delete Sector";
	lib[8].font_rect.x = 660;
	lib[8].font_rect.y = 300;
	lib[8].font_color = doom->lib.font_lib.font_color.black;
	lib[9].str = "Place player";
	lib[9].font_rect.x = 665;
	lib[9].font_rect.y = 380;
	lib[9].font_color = doom->lib.font_lib.font_color.black;
	set_editor_text_3(doom, lib);
}

static void	set_editor_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	char		**str;

	lib[0].len = len;
	lib[0].str = "Sector:";
	lib[0].font_rect.x = 45;
	lib[0].font_rect.y = 20;
	lib[0].font_color = doom->lib.font_lib.font_color.black;
	lib[1].str = "Select Wall";
	lib[1].font_rect.x = 670;
	lib[1].font_rect.y = 20;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "texture:";
	lib[2].font_rect.x = 685;
	lib[2].font_rect.y = 50;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
	lib[3].str = "Floor Height";
	lib[3].font_rect.x = 25;
	lib[3].font_rect.y = 120;
	lib[3].font_color = doom->lib.font_lib.font_color.black;
	lib[4].str = "Ceiling Height";
	lib[4].font_rect.x = 16;
	lib[4].font_rect.y = 185;
	lib[4].font_color = doom->lib.font_lib.font_color.black;
	set_editor_text_2(doom, lib);
}

void		save_game_editor_font(t_doom *doom, int *len)
{
	TTF_Font	*font;

	*len = 11;
	doom->lib.font_lib.game_editor_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.game_editor_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_editor_text(doom, doom->lib.font_lib.game_editor_font, *len);
	font = doom->lib.font_lib.font_20;
	font_to_sdl(doom, doom->lib.font_lib.game_editor_font, font);
}

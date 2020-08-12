/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:40:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/12 09:28:09 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_editor_text_3(t_doom *doom, t_font *lib)
{
	lib[10].str = "Make portal";
	lib[10].font_rect.x = 675;
	lib[10].font_rect.y = 196;
	lib[10].font_color = doom->lib.font_lib.font_color.black;
	lib[11].str = "Top texture";
	lib[11].font_rect.x = 675;
	lib[11].font_rect.y = 340;
	lib[11].font_color = doom->lib.font_lib.font_color.black;
	lib[12].str = "Mid texture";
	lib[12].font_rect.x = 680;
	lib[12].font_rect.y = 427;
	lib[12].font_color = doom->lib.font_lib.font_color.black;
	lib[13].str = "Bottom texture";
	lib[13].font_rect.x = 660;
	lib[13].font_rect.y = 500;
	lib[13].font_color = doom->lib.font_lib.font_color.black;
}

static void	set_editor_text_2(t_doom *doom, t_font *lib)
{
	lib[5].str = "Floor texture";
	lib[5].font_rect.x = 30;
	lib[5].font_rect.y = 340;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "Ceiling texture";
	lib[6].font_rect.x = 25;
	lib[6].font_rect.y = 510;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "Save";
	lib[7].font_rect.x = 110;
	lib[7].font_rect.y = 560;
	lib[7].font_color = doom->lib.font_lib.font_color.black;
	lib[8].str = "Exit";
	lib[8].font_rect.x = 20;
	lib[8].font_rect.y = 560;
	lib[8].font_color = doom->lib.font_lib.font_color.black;
	lib[9].str = "Player Position";
	lib[9].font_rect.x = 665;
	lib[9].font_rect.y = 110;
	lib[9].font_color = doom->lib.font_lib.font_color.black;
	set_editor_text_3(doom, lib);
}

static void	set_editor_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	char		**str;

	lib[0].len = len;
	lib[0].str = "Create Sector";
	lib[0].font_rect.x = 30;
	lib[0].font_rect.y = 40;
	lib[0].font_color = doom->lib.font_lib.font_color.black;
	lib[1].str = "Select Wall";
	lib[1].font_rect.x = 670;
	lib[1].font_rect.y = 40;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "Floor Height";
	lib[2].font_rect.x = 35;
	lib[2].font_rect.y = 120;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
	lib[3].str = "Ceiling Height";
	lib[3].font_rect.x = 30;
	lib[3].font_rect.y = 190;
	lib[3].font_color = doom->lib.font_lib.font_color.black;
	lib[4].str = "Light level";
	lib[4].font_rect.x = 40;
	lib[4].font_rect.y = 260;
	lib[4].font_color = doom->lib.font_lib.font_color.black;
	set_editor_text_2(doom, lib);
}

void		save_game_editor_font(t_doom *doom, int *len)
{
	TTF_Font	*font;
	int			font_size;

	*len = 14;
	doom->lib.font_lib.game_editor_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.game_editor_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_editor_text(doom, doom->lib.font_lib.game_editor_font, *len);
	font = doom->lib.font_lib.font_20;
	font_to_sdl(doom, doom->lib.font_lib.game_editor_font, font);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   start_menu_font.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 15:38:38 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 17:55:04 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text2(t_doom *doom, t_font *lib)
{
	lib[5].str = "Game Editor";
	lib[5].font_rect.x = WIDTH / 2.55;
	lib[5].font_rect.y = 375;
	lib[5].font_color = doom->lib.font_lib.font_color.blue;
	lib[6].str = "Press ESC to exit		\
			Press Y to pause game";
	lib[6].font_rect.x = WIDTH / 7;
	lib[6].font_rect.y = 550;
	lib[6].font_color = doom->lib.font_lib.font_color.red;
}

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Doomed: Corona Edition";
	lib[0].font_rect.x = WIDTH / 3.7;
	lib[0].font_rect.y = 50;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
	lib[1].str = "Select an option:";
	lib[1].font_rect.x = WIDTH / 2.9;
	lib[1].font_rect.y = 150;
	lib[1].font_color = doom->lib.font_lib.font_color.blue;
	lib[2].str = "Start Game";
	lib[2].font_rect.x = WIDTH / 2.5;
	lib[2].font_rect.y = 225;
	lib[2].font_color = doom->lib.font_lib.font_color.blue;
	lib[3].str = "Difficulty: 	1				2				3";
	lib[3].font_rect.x = WIDTH / 3;
	lib[3].font_rect.y = 300;
	lib[3].font_color = doom->lib.font_lib.font_color.blue;
	lib[4].str = "Player Settings";
	lib[4].font_rect.x = WIDTH / 2.7;
	lib[4].font_rect.y = 450;
	lib[4].font_color = doom->lib.font_lib.font_color.blue;
	set_text2(doom, lib);
}

void		save_start_menu_font(t_doom *doom, int *len)
{
	TTF_Font	*font;

	*len = 7;
	doom->lib.font_lib.start_menu_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.start_menu_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.start_menu_font, *len);
	font = doom->lib.font_lib.font_30;
	font_to_sdl(doom, doom->lib.font_lib.start_menu_font, font);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setting_window_font.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 15:40:14 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 16:56:47 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text_3(t_doom *doom, t_font *lib, int start)
{
	lib[9].str = "Select Player";
	lib[9].font_rect.x = WIDTH / 20;
	lib[9].font_rect.y = start * 0.5;
	lib[9].font_color = doom->lib.font_lib.font_color.blue;
	lib[10].str = "Righthanded				or				Lefthanded";
	lib[10].font_rect.x = WIDTH / 20;
	lib[10].font_rect.y = start * 1.5;
	lib[10].font_color = doom->lib.font_lib.font_color.blue;
	lib[11].str = "LEVEL EDITOR: To save game editor, press B to save, then\
	N to exit.";
	lib[11].font_rect.x = WIDTH / 20;
	lib[11].font_rect.y = start * 9.5;
	lib[11].font_color = doom->lib.font_lib.font_color.black;
	lib[12].str = "Press ESC anytime to exit";
	lib[12].font_rect.x = WIDTH / 20;
	lib[12].font_rect.y = start * 10.3;
	lib[12].font_color = doom->lib.font_lib.font_color.black;
	lib[13].str = "Back to menu";
	lib[13].font_rect.x = WIDTH / 2.41;
	lib[13].font_rect.y = start * 11.3;
	lib[13].font_color = doom->lib.font_lib.font_color.black;
}

static void	set_text_2(t_doom *doom, t_font *lib, int start)
{
	lib[4].str = "Press left mouse key to select. Press E again\
		to exit select mode.";
	lib[4].font_rect.x = WIDTH / 20;
	lib[4].font_rect.y = start * 5.5;
	lib[4].font_color = doom->lib.font_lib.font_color.black;
	lib[5].str = "To spray sanitizer, press E to activate spray mode.\
		Press left mouse key to";
	lib[5].font_rect.x = WIDTH / 20;
	lib[5].font_rect.y = start * 6.5;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "spray. Press E to exit spray mode.";
	lib[6].font_rect.x = WIDTH / 20;
	lib[6].font_rect.y = start * 7;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "To remove item from basket, press T to activate remove mode.\
		Press left mouse key on";
	lib[7].font_rect.x = WIDTH / 20;
	lib[7].font_rect.y = start * 8;
	lib[7].font_color = doom->lib.font_lib.font_color.black;
	lib[8].str = "item to remove. Press T to exit remove mode.";
	lib[8].font_rect.x = WIDTH / 20;
	lib[8].font_rect.y = start * 8.5;
	lib[8].font_color = doom->lib.font_lib.font_color.black;
	set_text_3(doom, lib, start);
}

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	int			start;

	start = HEIGHT / 12;
	lib[0].len = len;
	lib[0].str = "Movement: Press W to move foward, S to move backwards,";
	lib[0].font_rect.x = WIDTH / 20;
	lib[0].font_rect.y = start * 2.5;
	lib[0].font_color = doom->lib.font_lib.font_color.black;
	lib[1].str = "A to move left, D to move right.";
	lib[1].font_rect.x = WIDTH / 20;
	lib[1].font_rect.y = start * 3;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "To jump, press the Spacebar. To bend, press the X key.";
	lib[2].font_rect.x = WIDTH / 20;
	lib[2].font_rect.y = start * 4;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
	lib[3].str = "To select an item, such as a grocery, press E to activate\
		select mode.";
	lib[3].font_rect.x = WIDTH / 20;
	lib[3].font_rect.y = start * 5;
	lib[3].font_color = doom->lib.font_lib.font_color.black;
	set_text_2(doom, lib, start);
}

void		save_setting_window_font(t_doom *doom, int *len)
{
	TTF_Font	*font;

	*len = 14;
	doom->lib.font_lib.setting_menu_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.setting_menu_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.setting_menu_font, *len);
	font = doom->lib.font_lib.font_20;
	font_to_sdl(doom, doom->lib.font_lib.setting_menu_font, font);
}

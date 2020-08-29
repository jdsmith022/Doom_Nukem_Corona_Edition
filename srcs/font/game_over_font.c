/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_over_font.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 15:40:46 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 15:23:15 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"
#include "../../includes/hud.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "GAME OVER!";
	lib[0].font_rect.x = WIDTH / 2.65;
	lib[0].font_rect.y = 200;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
	lib[1].str = "You're corona level reached 100!";
	lib[1].font_rect.x = WIDTH / 4.5;
	lib[1].font_rect.y = 275;
	lib[1].font_color = doom->lib.font_lib.font_color.green;
	lib[2].str = "Time to self-quarantine!";
	lib[2].font_rect.x = WIDTH / 3.4;
	lib[2].font_rect.y = 325;
	lib[2].font_color = doom->lib.font_lib.font_color.green;
	lib[3].str = "Press ESC to exit";
	lib[3].font_rect.x = WIDTH / 2.7;
	lib[3].font_rect.y = 500;
	lib[3].font_color = doom->lib.font_lib.font_color.green;
}

void		save_game_over_font(t_doom *doom, int *len)
{
	TTF_Font	*font;

	*len = 4;
	doom->lib.font_lib.game_over_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.game_over_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.game_over_font, *len);
	font = doom->lib.font_lib.font_30;
	font_to_sdl(doom, doom->lib.font_lib.game_over_font, font);
}

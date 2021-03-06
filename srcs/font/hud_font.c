/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/23 15:39:34 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 15:21:38 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"

static void	set_timer(t_doom *doom, t_font *lib)
{
	lib[6].str = "Time";
	lib[6].font_rect.x = WIDTH / 2.4;
	lib[6].font_rect.y = 15;
	lib[6].font_color = doom->lib.font_lib.font_color.white;
}

static void	set_levels(t_doom *doom, t_font *lib)
{
	lib[4].str = "0%";
	lib[4].font_rect.x = 175;
	lib[4].font_rect.y = HEIGHT - 35;
	lib[4].font_color = doom->lib.font_lib.font_color.white;
	lib[5].str = "100%";
	lib[5].font_rect.x = WIDTH - 250;
	lib[5].font_rect.y = HEIGHT - 35;
	lib[5].font_color = doom->lib.font_lib.font_color.white;
	set_timer(doom, lib);
}

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Corona Level";
	lib[0].font_rect.x = 10;
	lib[0].font_rect.y = HEIGHT - 35;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
	lib[1].str = "Sanitizer Level";
	lib[1].font_rect.x = WIDTH - 175;
	lib[1].font_rect.y = HEIGHT - 35;
	lib[1].font_color = doom->lib.font_lib.font_color.blue;
	lib[2].str = "Shopping List";
	lib[2].font_rect.x = WIDTH - 160;
	lib[2].font_rect.y = 15;
	lib[2].font_color = doom->lib.font_lib.font_color.red;
	lib[3].str = "Basket";
	lib[3].font_rect.x = 10;
	lib[3].font_rect.y = 15;
	lib[3].font_color = doom->lib.font_lib.font_color.red;
	set_levels(doom, lib);
}

void		save_hud_font(t_doom *doom, int *len)
{
	TTF_Font	*font;

	*len = 7;
	doom->lib.font_lib.hud_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.hud_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.hud_font, *len);
	font = doom->lib.font_lib.font_22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font);
}

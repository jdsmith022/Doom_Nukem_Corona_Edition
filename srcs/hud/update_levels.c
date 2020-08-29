/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_levels.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:16:17 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:16:17 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"

static void	update_sanitizer_levels(t_doom *doom, t_font *lib,
				int level, char *sanitizer_level)
{
	TTF_Font	*font;

	lib[5].str = sanitizer_level;
	lib[5].font_rect.x = WIDTH - 250;
	lib[5].font_rect.y = HEIGHT - 35;
	if (level < 15)
		lib[5].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[5].font_color = doom->lib.font_lib.font_color.white;
	font = doom->lib.font_lib.font_22;
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[5], font);
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[0], font);
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[1], font);
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[2], font);
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[3], font);
}

void	update_levels(t_doom *doom, t_font *lib)
{
	TTF_Font	*font;
	int			level;
	char		*corona_level;
	char		*sanitizer_level;
	char		*percent;

	level = doom->hud->corona_level;
	corona_level = ft_itoa(level);
	percent = ft_strcat(corona_level, "%");
	lib[4].str = corona_level;
	lib[4].font_rect.x = 175;
	lib[4].font_rect.y = HEIGHT - 35;
	if (level > 84)
		lib[4].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[4].font_color = doom->lib.font_lib.font_color.white;
	level = doom->hud->sanitizer_level;
	sanitizer_level = ft_itoa(level);
	percent = ft_strcat(sanitizer_level, "%");
	update_sanitizer_levels(doom, lib, level, sanitizer_level);
	font = doom->lib.font_lib.font_22;
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[4], font);
	free(corona_level);
	free(sanitizer_level);
}

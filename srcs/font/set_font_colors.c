/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_font_colors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:47:57 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/24 22:00:19 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_font_colors_2(t_doom *doom)
{
	SDL_Color color;

	color = doom->lib.font_lib.font_color.blue;
	color.r = 14;
	color.g = 188;
	color.b = 223;
	doom->lib.font_lib.font_color.blue = color;
}

void		set_font_colors(t_doom *doom)
{
	SDL_Color color;

	color = doom->lib.font_lib.font_color.white;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	doom->lib.font_lib.font_color.white = color;
	color = doom->lib.font_lib.font_color.black;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	doom->lib.font_lib.font_color.black = color;
	color = doom->lib.font_lib.font_color.green;
	color.r = 0;
	color.g = 204;
	color.b = 0;
	doom->lib.font_lib.font_color.green = color;
	color = doom->lib.font_lib.font_color.red;
	color.r = 204;
	color.g = 0;
	color.b = 0;
	doom->lib.font_lib.font_color.red = color;
	set_font_colors_2(doom);
}

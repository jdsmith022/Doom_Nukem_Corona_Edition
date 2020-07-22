/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_font_colors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:47:57 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/22 21:17:27 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	set_font_colors(t_doom *doom)
{
	SDL_Color color;

	color = doom->lib.font_color.white;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	doom->lib.font_color.white = color;
	color = doom->lib.font_color.black;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	doom->lib.font_color.black = color;
	color = doom->lib.font_color.green;
	color.r = 0;
	color.g = 204;
	color.b = 0;
	doom->lib.font_color.green = color;
	color = doom->lib.font_color.red;
	color.r = 204;
	color.g = 0;
	color.b = 0;
	doom->lib.font_color.red = color;
}

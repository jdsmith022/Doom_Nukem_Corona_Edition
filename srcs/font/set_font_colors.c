/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_font_colors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:47:57 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/22 14:58:02 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	set_font_color(t_doom *doom)
{
	SDL_Color color;

	color = doom->lib.game_editor_font->white;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	doom->lib.game_editor_font->white = color;
	color = doom->lib.game_editor_font->black;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	doom->lib.game_editor_font->black = color;
	color = doom->lib.game_editor_font->green;
	color.r = 0;
	color.g = 204;
	color.b = 0;
	doom->lib.game_editor_font->green = color;
	color = doom->lib.game_editor_font->red;
	color.r = 204;
	color.g = 0;
	color.b = 0;
	doom->lib.game_editor_font->red = color;
}

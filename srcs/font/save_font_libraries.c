/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font_libraries.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 20:23:13 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/23 09:36:13 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	save_font_libraries(t_doom *doom)
{
	set_font_colors(doom);
	save_game_editor_font(doom, &doom->lib.font_lib.ge_font_len);
	save_hud_font(doom, &doom->lib.font_lib.hud_font_len);
	save_basket_font(doom, &doom->lib.font_lib.basket_font_len);
}

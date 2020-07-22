/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font_libraries.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 20:23:13 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/22 21:19:57 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	save_font_libraries(t_doom *doom)
{
    set_font_colors(doom);
    save_game_editor_font(doom, &doom->lib.ge_font_len);
    // save_hud_font(doom, &doom->lib.hud_font->len);
}

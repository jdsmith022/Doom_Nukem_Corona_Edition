/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font_libraries.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:11:19 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 15:11:20 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	save_font_libraries(t_doom *doom)
{
	init_hud(doom);
	set_font_colors(doom);
	set_font_style(doom);
	save_game_editor_font(doom, &doom->lib.font_lib.ge_font_len);
	save_hud_font(doom, &doom->lib.font_lib.hud_font_len);
	save_start_menu_font(doom, &doom->lib.font_lib.start_font_len);
	save_setting_window_font(doom, &doom->lib.font_lib.setting_font_len);
	save_game_over_font(doom, &doom->lib.font_lib.game_font_len);
	save_instruction_font(doom, &doom->lib.font_lib.instruction_font_len);
	save_pause_font(doom, &doom->lib.font_lib.pause_font_len);
}

#include "../../includes/doom.h"

void	save_font_libraries(t_doom *doom)
{
	set_font_colors(doom);
	save_game_editor_font(doom, &doom->lib.font_lib.ge_font_len);
	save_hud_font(doom, &doom->lib.font_lib.hud_font_len);
	save_start_menu_font(doom, &doom->lib.font_lib.start_font_len);
	save_setting_window_font(doom, &doom->lib.font_lib.setting_font_len);
}

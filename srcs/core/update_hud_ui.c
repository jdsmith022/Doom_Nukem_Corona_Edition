
#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void		update_hud_ui(t_doom *doom)
{
	font_timer(doom);
	font_to_screen(doom);
	update_hud(doom);
	menus(doom);
}

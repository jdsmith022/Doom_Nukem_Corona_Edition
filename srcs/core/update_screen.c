
#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void		update_screen(t_doom *doom)
{
	font_timer(doom);
	update_hud(doom);
	menus(doom);
}

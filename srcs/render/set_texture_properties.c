#include "../../includes/doom.h"

void    set_texture_properties(t_doom *doom, t_sector sector, int texture, int d)
{
	(void)d;
	doom->texture_width = 96;
	doom->texture_height = 96;
	doom->vertical_height_std = doom->texture_height;
}

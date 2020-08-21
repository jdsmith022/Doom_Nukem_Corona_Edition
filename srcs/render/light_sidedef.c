#include "../../includes/doom.h"

void		add_tint_to_color(Uint32 *color, int tint)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	r = ((*color >> 16) & 0xFF);
	g = ((*color >> 8) & 0xFF);
	b = (*color & 0xFF);
	if (tint == BLUE)
		b += 20;
	else if (tint == RED)
		r += 20;
	else
		g += 20;
	*color = (r << 16 | g << 8 | b);
}

void			light_sidedef(t_doom *doom, t_sidedef sidedef, int x)
{
	if (doom->light == TRUE)
	{
		if (doom->lib.sector[sidedef.sector].light == TRUE)
			doom->distance = doom->lib.sector[sidedef.sector].light_level;
		else
			doom->distance = 0.15;
	}
	else
	{
		doom->distance = 1 / (doom->distance / 70);
		doom->distance = x > WIDTH / 2 ? \
			doom->distance - (x - (float)WIDTH / 2.0) * X_CHANGE :\
			+doom->distance - ((float)WIDTH / 2.0 - x) * X_CHANGE;
	}
}

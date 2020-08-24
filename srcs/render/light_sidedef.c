#include "../../includes/doom.h"

void		add_tint_to_color(Uint32 *color, int tint, int mask)
{
	Uint8	r;
	Uint8	g;
	Uint8	b;

	r = ((*color >> 16) & mask);
	g = ((*color >> 8) & mask);
	b = (*color & mask);
	if (tint == BLUE)
		b += 30;
	else if (tint == RED)
		r += 30;
	else
		g += 30;
	*color = (r << 16 | g << 8 | b);
}

void		light_sidedef(t_doom *doom, t_sidedef sidedef, int x)
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
		if (x > (WIDTH / 2))
			doom->distance -= (x - (float)WIDTH / 2.0) * (1.0 / (float)HEIGHT);
		else
			doom->distance = +doom->distance - ((float)WIDTH / 2.0 - x) * \
				(1.0 / (float)WIDTH);
	}
}

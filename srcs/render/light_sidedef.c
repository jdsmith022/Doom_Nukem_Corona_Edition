#include "../../includes/doom.h"

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

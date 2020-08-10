#include "../../includes/doom.h"

void				scissor_lift_up(t_doom *doom)
{
	double		max_height;

	printf("doom->texture_height = %d\n", doom->texture_height);
	max_height = doom->texture_height +\
	doom->lib.sector[doom->i_sector].height_ceiling + 200;
	if (doom->own_event.scissor_lift_up == TRUE &&\
	doom->player_height <= max_height)
	{
		doom->player_height += 10;
		printf("GOING UP %f\n", doom->player_height);
		// doom->own_event.scissor_lift_up = FALSE;
	}
}

void				scissor_lift_down(t_doom *doom)
{
	if (doom->own_event.scissor_lift_down == TRUE)
	{
		if (doom->player_height > doom->player_std_height)
			doom->player_height -= 10;
		printf("GOING DOWN %f\n", doom->player_height);
		if (doom->player_height == doom->player_std_height)
			exit_scissor_lift(doom);
		// doom->own_event.scissor_lift_down = FALSE;
	}
}

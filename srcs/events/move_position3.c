#include "../../includes/doom.h"

void				scissor_lift_up(t_doom *doom)
{
	double		max_height;

	printf("doom->texture_height = %d\n", doom->texture_height);
	max_height = doom->texture_height +\
	doom->lib.sector[doom->i_sector].height_ceiling + 20;
	while (doom->own_event.scissor_lift_up == TRUE &&\
	doom->player_height <= max_height)
	{
		doom->player_height += 1;
		printf("GOING UP %f\n", doom->player_height);
	}
}

void				scissor_lift_down(t_doom *doom)
{
	while (doom->own_event.scissor_lift_down == TRUE &&\
	doom->player_height > doom->player_std_height)
	{
		doom->player_height -= 1;
		printf("GOING DOWN %f\n", doom->player_height);
		if (doom->player_height == doom->player_std_height)
			exit_scissor_lift(doom);
	}
}

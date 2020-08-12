#include "../../includes/doom.h"
#include "../../includes/hud.h"

void	player_fall(t_doom *doom, t_sprite *sprite)
{
	double	min_height;

	min_height = 0.0;
	sprite->action = 8;
	if (doom->player_height > min_height)
	{
		doom->hud->boxes = TRUE;
		doom->own_event.fall = TRUE;
		doom->lib.font_lib.bools.text = TRUE;
		doom->player_height = min_height;
		if (doom->own_event.cam_move_b == TRUE ||
		doom->own_event.cam_move_l == TRUE)
		{
			doom->own_event.y_pitch = -240;
			if (doom->own_event.fall_count > 0)
				doom->own_event.fall_count = 1;
		}
		else
		{
			doom->own_event.y_pitch = 240;
			if (doom->own_event.fall_count != -1)
				doom->own_event.fall_count *= -1;
		}
	}
}

void				scissor_lift_up(t_doom *doom)
{
	double		max_height;

	// printf("doom->texture_height = %d\n", doom->texture_height);
	max_height = doom->texture_height +\
	doom->lib.sector[doom->i_sector].height_ceiling + 200;
	// printf("after calculating max_height\n");
	if (doom->own_event.scissor_lift_up == TRUE &&\
	doom->player_height <= max_height)
	{
		doom->player_height += 10;
		// printf("GOING UP %f\n", doom->player_height);
		// doom->own_event.scissor_lift_up = FALSE; //don't need it, press up and down
	}
}

void				scissor_lift_down(t_doom *doom)
{
	if (doom->own_event.scissor_lift_down == TRUE)
	{
		if (doom->player_height > doom->player_std_height)
			doom->player_height -= 10;
		// printf("GOING DOWN %f\n", doom->player_height);
		if (doom->player_height == doom->player_std_height)
			exit_scissor_lift(doom);
		// doom->own_event.scissor_lift_down = FALSE; //don't need it, it's press up and down
	}
}

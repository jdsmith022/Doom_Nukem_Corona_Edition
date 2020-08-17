#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/action.h"

void	player_fall(t_doom *doom, t_sprite *sprite)
{
	double	min_height;
	t_event	*event;

	event = &doom->own_event;
	if (event->scissor_lift == FALSE)
	{
		min_height = 0.0;
		sprite->action = 8;
		if (doom->player_height > min_height)
		{
			if (event->fall_count == -1)
				doom->lib.font_lib.bools.text = TRUE;
			event->fall = TRUE;
			doom->hud->boxes = TRUE;
			event->died = FALSE;
			doom->player_height = min_height;
			if (event->cam_move_b == TRUE ||
			event->cam_move_l == TRUE)
				event->y_pitch = -200;
			else
				event->y_pitch = 200;
		}
	}
}

void				scissor_lift_up(t_doom *doom)
{
	double	max_height;
	t_event	*event;

	event = &doom->own_event;
	printf("up\n");
	max_height = doom->texture_height +\
	doom->lib.sector[doom->i_sector].height_ceiling + 50;
	if (event->scissor_lift_up == TRUE &&\
	doom->player_height <= max_height)
	{
		doom->player_height += 10;
		if (doom->player_height > max_height)
			doom->player_height = max_height;
		event->y_pitch += 20;
		if (event->y_pitch > 400)
			event->y_pitch = 400;
		printf("up pitch: %d\n", event->y_pitch);
	}
}

void				scissor_lift_down(t_doom *doom)
{
	t_event	*event;

	event = &doom->own_event;
	printf("down pitch: %d\n", event->y_pitch);
	if (event->scissor_lift_down == TRUE)
	{
		if (doom->player_height >= 50)
		{
			doom->player_height -= 10;
			// event->y_pitch += 10;
			// if (event->y_pitch > 240)
			// 	event->y_pitch = 240;
			doom->player_height -= 10;
		}
		if (doom->player_height < 50)
			doom->player_height = 50;

		// printf("GOING DOWN %f\n", doom->player_height);
		// if (doom->player_height == 58)
		// 	exit_scissor_lift(doom);
		// event->scissor_lift_down = FALSE; //don't need it, it's press up and down
	}
}

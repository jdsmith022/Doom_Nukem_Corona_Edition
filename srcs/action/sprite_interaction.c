#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/action.h"
static void	fall_direction(t_doom *doom)
{
	int		fall_direction;
	t_event	*event;

	event = &doom->own_event;

	if (event->cam_move_b == TRUE ||
	event->cam_move_l == TRUE) //work on fall backwards
		fall_direction = 10;
	else
		fall_direction = -10;
	if (event->y_pitch < 200 && event->y_pitch > -200)
		event->y_pitch += (fall_direction * GRAVITY);
	if (event->y_pitch < -200)
		event->y_pitch = -200;
	if (event->y_pitch > 200)
		event->y_pitch = 200;

}

void	player_fall(t_doom *doom)
{
	double	min_height;
	static double duration = -0.2;
	t_event	*event;

	event = &doom->own_event;
	if (event->scissor_lift == FALSE)
	{
		min_height = 0.0;
		if (doom->player_height > min_height)
		{
			if (event->fall_count == -1)
				doom->lib.font_lib.bools.text = TRUE;
			doom->hud->boxes = TRUE;
			event->died = FALSE;
			doom->player_height -= 20; //- (GRAVITY * (duration + 0.05));
			fall_direction(doom);
		}
	}
	printf("end of fall\n");
}

void				scissor_lift_up(t_doom *doom)
{
	double	max_height;
	t_event	*event;

	event = &doom->own_event;
	printf("up\n");
	max_height = doom->texture_height + 250;
	if (doom->player_height <= max_height)
	{
		printf("lift up\n");
		doom->player_height += 20;
		doom->up += 1;
		// if (doom->own_event.y_pitch < 1000)
		// 	doom->own_event.y_pitch += 20;
		if (doom->player_height > max_height)
		{
			doom->player_height = max_height;
			event->scissor_lift_up = FALSE;
		}
		printf("up pitch: %d --- height: %f\n", event->y_pitch, doom->player_height);
	}
}

void				scissor_lift_down(t_doom *doom)
{
	t_event	*event;

	event = &doom->own_event;
	printf("down pitch: %d\n", event->y_pitch);
	if (doom->player_height >= 50)
	{
		doom->player_height -= 20;
		doom->up -= 1;
		// event->y_pitch -= 20;
		// if (event->y_pitch > 140)
		// 	event->y_pitch = 140;
	}
	if (doom->player_height < 50)
	{
		doom->player_height = 50;
		event->scissor_lift_down = FALSE;
		doom->up = 0;
	}
	printf("GOING DOWN %f\n", doom->player_height);
	// if (doom->player_height == 58)
	// 	exit_scissor_lift(doom);
	// event->scissor_lift_down = FALSE; //don't need it, it's press up and down
}

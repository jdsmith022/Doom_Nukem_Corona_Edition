#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/action.h"

static void	fall_direction(t_doom *doom)
{
	int		fall_direction;
	t_event	*event;

	event = &doom->own_event;
	if (event->move_pos_f == TRUE)
		fall_direction = -10;
	else
		fall_direction = 10;
	if (event->y_pitch < 200 && event->y_pitch > -250)
		event->y_pitch += (fall_direction * GRAVITY);
	if (event->y_pitch < -250)
		event->y_pitch = -250;
	if (event->y_pitch > 200)
		event->y_pitch = 200;
}

void	player_fall(t_doom *doom)
{
	int				min_height;
	static double	duration = -0.2;
	t_event			*event;

	event = &doom->own_event;
	if (event->scissor_lift == FALSE)
	{
		min_height = doom->lib.sector[doom->i_sector].height_floor + 10;
		if (doom->player_height > min_height)
		{
			if (event->fall_count == -1)
				doom->lib.font_lib.bools.text = TRUE;
			doom->player_height -= 20 - (GRAVITY * (duration + 0.05));
			if (doom->player_height < min_height)
				doom->player_height = min_height;
			doom->hud->boxes = TRUE;
			event->died = FALSE;
			fall_direction(doom);
		}
	}
}

void				scissor_lift_up(t_doom *doom)
{
	int		max_height;
	t_event	*event;

	event = &doom->own_event;;
	max_height = doom->texture_height + \
		doom->lib.sector[doom->i_sector].height_ceiling - (PLAYER_HEIGHT / 2);
	if (doom->player_height <= max_height)
	{
		doom->player_height += 20;
		if (doom->player_height > max_height)
		{
			doom->player_height = max_height;
			event->scissor_lift_up = FALSE;
		}
	}
	printf("end of lift\n");
}

void				scissor_lift_down(t_doom *doom)
{
	t_event	*event;

	event = &doom->own_event;
	if (doom->player_height >= 50)
	{
		doom->player_height -= 20;
		event->y_pitch = 0;
	}
	if (doom->player_height < 50)
	{
		doom->player_height = 50;
		event->scissor_lift_down = FALSE;
	}
}

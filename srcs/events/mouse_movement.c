
#include "../../includes/doom.h"
#include "../editor/game_editor.h"
#include "../../includes/events.h"

static double	to_radians(int degrees)
{
	return (degrees * (PI / 180));
}

static void		set_pitch(t_doom *doom, SDL_MouseMotionEvent *motion,
					t_event *event)
{
	int next_pitch;
	int limit_pos;
	int limit_neg;

	if (doom->own_event.scissor_lift == TRUE)
	{
		limit_pos = 400;
		limit_neg = 50;
	}
	else
	{
		limit_pos = 350;
		limit_neg = -350;
	}
	event->y_pitch = event->y_pitch > limit_pos ? limit_pos : event->y_pitch;
	event->y_pitch = event->y_pitch < limit_neg ? limit_neg : event->y_pitch;
	next_pitch = event->y_pitch + (motion->yrel * SENSITIVITY);
	if (next_pitch <= limit_pos && next_pitch >= limit_neg)
		event->y_pitch += motion->yrel;
	if (event->y_pitch > limit_pos)
		event->y_pitch = limit_pos;
	if (event->y_pitch < limit_neg)
		event->y_pitch = limit_neg;
	doom->own_event.hold_x = motion->x;
	doom->own_event.hold_y = motion->y;
}

static void		cam_movement(t_doom *doom, SDL_MouseMotionEvent *motion,
					double dt, t_event *event)
{
	double	radian;
	int		dir_x;
	int		dir_y;

	radian = PI / 180;
	dir_x = 1;
	dir_y = 1;
	doom->dir_angle += to_radians(motion->xrel) * SENSITIVITY;
	set_pitch(doom, motion, event);
}

void			move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,
	double dt, t_event *event)
{
	SDL_GetMouseState(&doom->own_event.hold_x, &doom->own_event.hold_y);
	if (event->mouse_pointer == TRUE)
		SDL_SetRelativeMouseMode(FALSE);
	else {
		SDL_SetRelativeMouseMode(TRUE);
		cam_movement(doom, motion, dt, event);
	}
}

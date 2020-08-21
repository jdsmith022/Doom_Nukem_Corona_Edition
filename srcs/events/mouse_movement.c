
#include "../../includes/doom.h"
#include "../editor/game_editor.h"

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
		limit_pos = 300;
		limit_neg = 50;
	}
	else
	{
		limit_pos = 200;
		limit_neg = -200;
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

void	move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,
	double dt, t_event *event)
{
	SDL_GetMouseState(&doom->own_event.hold_x, &doom->own_event.hold_y);
	if (event->select == TRUE && event->shoot == FALSE)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		SDL_SetCursor(doom->cursor);
	}
	else if (event->shoot == TRUE && event->select == FALSE)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		doom->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR);
		SDL_SetCursor(doom->cursor);
	}
	else if ((event->select == FALSE && event->shoot == FALSE) || \
		(event->select == TRUE && event->shoot == TRUE))
	{
		if (event->select == TRUE && event->shoot == TRUE)
		{
			event->select = FALSE;
			event->shoot = FALSE;
		}
		SDL_SetRelativeMouseMode(SDL_TRUE);
	}
	cam_movement(doom, motion, dt, event);
}

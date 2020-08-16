
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

	event->y_pitch = event->y_pitch > 300 ? 300 : event->y_pitch;
	event->y_pitch = event->y_pitch < -300 ? -300 : event->y_pitch;
	next_pitch = event->y_pitch + (motion->yrel * SENSITIVITY);
	if (next_pitch <= 300 && next_pitch >= -300)
		event->y_pitch += motion->yrel;
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
	if (doom->own_event.scissor_lift == FALSE)
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

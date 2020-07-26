#include "../../includes/doom.h"
#include "../editor/game_editor.h"

static void		set_pitch(t_doom *doom, SDL_MouseMotionEvent *motion,
					t_event *event)
{
	if (motion->yrel > 0)
	{
		if (event->y_pitch < 200)
			event->y_pitch += 20;
	}
	if (motion->yrel < 0)
	{
		if (event->y_pitch > -250)
			event->y_pitch -= 20;
	}
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
	if (motion->xrel < 0)
		dir_x = -1;
	if (motion->yrel < 0)
		dir_y = -1;
	if (motion->yrel < 1)
		doom->dir_angle += CAM_SPEED * dir_x * dt;
	if (doom->dir_angle < 0)
		doom->dir_angle += 360 * radian;
	if (doom->dir_angle > 360 * radian)
		doom->dir_angle -= 360 * radian;
	set_pitch(doom, motion, event);
}

void	move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,
	double dt, t_event *event)
{
	SDL_GetMouseState(&doom->own_event.hold_x, &doom->own_event.hold_y);
	if (event->select == FALSE)
	{
		SDL_ShowCursor(SDL_DISABLE);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		cam_movement(doom, motion, dt, event);
	}
	else
	{
		SDL_ShowCursor(SDL_ENABLE);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}

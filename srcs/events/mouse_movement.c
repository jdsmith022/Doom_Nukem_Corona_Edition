/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_movement.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:48 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/02 18:52:35 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/events.h"
#include "../../includes/game_editor.h"

static double	to_radians(int degrees)
{
	return (degrees * (PI / 180));
}

static void		set_pitch(t_doom *doom, SDL_MouseMotionEvent *motion, double dt,
					t_event *event)
{
	int next_pitch;
	int limit_pos;
	int limit_neg;

	printf("top of mouse\n");
	if (doom->own_event.scissor_lift == TRUE)
	{
		limit_pos = 400;
		limit_neg = 50;
	}
	else
	{
		limit_pos = 300;
		limit_neg = -300;
	}
	event->y_pitch = event->y_pitch > limit_pos ? limit_pos : event->y_pitch;
	event->y_pitch = event->y_pitch < limit_neg ? limit_neg : event->y_pitch;
	next_pitch = event->y_pitch + (motion->yrel * (SENSITIVITY * (dt * 2)));
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
	doom->cast.dir_angle += to_radians(motion->xrel) * (SENSITIVITY * (dt * 2));
	set_pitch(doom, motion, dt, event);
}

static void		check_mouse_parameters(t_doom *doom)
{
	t_event *event;

	event = &doom->own_event;
	if (event->hold_x < 0)
		event->hold_x = 0;
	else if (event->hold_x > WIDTH)
		event->hold_x = WIDTH;
	if (event->hold_y < 0)
		event->hold_y = 0;
	else if (event->hold_y > HEIGHT)
		event->hold_y = HEIGHT;
}

void			move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,
					double dt, t_event *event)
{
	SDL_GetMouseState(&doom->own_event.hold_x, &doom->own_event.hold_y);
	check_mouse_parameters(doom);
	if (event->mouse_pointer == TRUE)
		SDL_SetRelativeMouseMode(FALSE);
	else
	{
		SDL_SetRelativeMouseMode(TRUE);
		cam_movement(doom, motion, dt, event);
	}
}

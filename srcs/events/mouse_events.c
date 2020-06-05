/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:56:09 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/05 21:00:34 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	camera_movement(t_doom *doom, SDL_MouseMotionEvent *motion, double dt)
{
	double radian;

	radian = PI / 180;
	dt = 0.0;
	if (doom->own_event.mouse_press == 1)
	{
		if (motion->x > doom->own_event.hold_x &&\
			motion->y <= HEIGHT && motion->y >= 0)
		{
			doom->dir_angle += 2 * radian;
			if (doom->dir_angle > 360 * radian)
				doom->dir_angle -= 360 * radian;
		}
		else if (motion->x < doom->own_event.hold_x &&\
			motion->y <= HEIGHT && motion->y >= 0)
		{
			doom->dir_angle -= 2 * radian;
			if (doom->dir_angle < 0)
				doom->dir_angle += 360 * radian;
		}
		doom->own_event.hold_x = motion->x;
	}
}

void	mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
		doom->own_event.mouse_press = 0;
}

void	mouse_press(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = button->x;
		doom->own_event.mouse_press = 1;
	}
}

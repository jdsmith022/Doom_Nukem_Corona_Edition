/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:56:09 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/11 13:21:09 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,\
	double dt)
{
	double	radian;
	int		cam_direction;

	radian = PI / 180;
	cam_direction = doom->own_event.hold_x - motion->x;
	doom->dir_angle -= CAM_SPEED * cam_direction * dt;
	if (doom->dir_angle < 0)
		doom->dir_angle += 360 * radian;
	if (doom->dir_angle > 360 * radian)
		doom->dir_angle -= 360 * radian;
	doom->own_event.hold_x = motion->x;
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

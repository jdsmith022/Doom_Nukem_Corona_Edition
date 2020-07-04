/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:56:09 by Malou         #+#    #+#                 */
/*   Updated: 2020/07/04 16:55:41 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../editor/game_editor.h"

#include <stdio.h>

void	move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,\
	double dt)
{
	double	radian;
	int		dir_x;
	int		dir_y;

	(void)dt;
	radian = PI / 180;
	dir_x = 1;
	dir_y = 1;
	// printf("%d\n", motion->xrel);
	if (motion->xrel < 0)
		dir_x = -1;
	if (motion->yrel < 0)
		dir_y = -1;
	if (motion->yrel < 1)
		doom->dir_angle += CAM_SPEED * dir_x * 0.05;
	//doom->own_event.y_pitch += CAM_SPEED * dir_y * dt;
	if (doom->dir_angle < 0)
		doom->dir_angle += 360 * radian;
	if (doom->dir_angle > 360 * radian)
		doom->dir_angle -= 360 * radian;
	doom->own_event.hold_x = motion->x;
	doom->own_event.hold_y = motion->y;
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
	if (doom->game_editor == TRUE)
		mouse_press_game_editor(doom, button->x, button->y);
}

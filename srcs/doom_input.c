/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 21:17:35 by Malou          #+#    #+#                */
/*   Updated: 2020/04/07 10:55:45 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	doom_mouse_motion(t_doom *doom, SDL_MouseMotionEvent *motion)
{
	double radian;

	radian = PI / 180;
	if (doom->own_event.mouse_press == 1)
	{
		if (motion->x > doom->own_event.hold_x && motion->y <= HEIGHT && motion->y >=0)
		{
			doom->dir_angle += 2 * radian;
			if (doom->dir_angle > 360 * radian)
				doom->dir_angle -= 360 * radian;
		}
		else if (motion->x < doom->own_event.hold_x && motion->y <= HEIGHT && motion->y >=0)
		{
			doom->dir_angle -= 2 * radian;
			if (doom->dir_angle < 0)
				doom->dir_angle += 360 * radian;
		}
		doom->own_event.hold_x = motion->x;
	}
}

void	doom_mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
		doom->own_event.mouse_press = 0;
}

void	doom_mouse_press(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = button->x;
		doom->own_event.mouse_press = 1;
	}
}

void	doom_key_input(t_doom *doom, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_ESCAPE)
		doom->esc = 1;
	if (key->keysym.sym == SDLK_a || key->keysym.sym == SDLK_d\
			|| key->keysym.sym == SDLK_w || key->keysym.sym == SDLK_s)
		move_player_position(doom, key->keysym.sym);
}

void	doom_input(t_doom *doom)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			doom_key_input(doom, &event.key);
		if (event.type == SDL_QUIT)
            doom->esc = 1;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			doom_mouse_press(doom, &event.button);
		if (event.type == SDL_MOUSEMOTION)
			doom_mouse_motion(doom, &event.motion);
		if (event.type == SDL_MOUSEBUTTONUP)
			doom_mouse_release(doom, &event.button);
	}
}
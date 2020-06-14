/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_events.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:33:01 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/11 18:33:24 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->cam_move_f == TRUE)
		cam_move_fb(doom, dt, MOVE_SPEED);
	else if (event->cam_move_b == TRUE)
		cam_move_fb(doom, dt, -MOVE_SPEED);
	else if (event->cam_move_l == TRUE)
		cam_move_rl(doom, dt, -90 * PI / 180);
	else if (event->cam_move_r == TRUE)
		cam_move_rl(doom, dt, 90 * PI / 180);
	if (event->jump == TRUE)
		jump_player(doom, dt);
	if (event->step_down == TRUE)
		step_down(doom, dt);
	if (event->bend == TRUE || \
		doom->player_height < 100 + doom->sector[doom->i_sector].height_floor)
		bend_down(doom);
}

void	key_release(t_event *event, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		event->cam_move_f = FALSE;
	else if (key->keysym.sym == SDLK_s)
		event->cam_move_b = FALSE;
	else if (key->keysym.sym == SDLK_a)
		event->cam_move_l = FALSE;
	else if (key->keysym.sym == SDLK_d)
		event->cam_move_r = FALSE;
	if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

void	key_press(t_doom *doom, t_event *event, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_ESCAPE)
		doom->is_running = FALSE;
	else if (key->keysym.sym == SDLK_w)
		event->cam_move_f = TRUE;
	else if (key->keysym.sym == SDLK_s)
		event->cam_move_b = TRUE;
	else if (key->keysym.sym == SDLK_a)
		event->cam_move_l = TRUE;
	else if (key->keysym.sym == SDLK_d)
		event->cam_move_r = TRUE;
	if (key->keysym.sym == SDLK_SPACE)
		event->jump = TRUE;
	if (key->keysym.sym == SDLK_x)
		event->bend = 1;
	if (key->keysym.sym == SDLK_UP)
		event->y_pitch += 10;
	if (key->keysym.sym == SDLK_DOWN)
		event->y_pitch -= 10;
}

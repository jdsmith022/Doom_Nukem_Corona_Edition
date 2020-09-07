/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_events.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 12:40:57 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/menu.h"
#include "../../includes/action.h"
#include "../../includes/sprites.h"
#include "../../includes/events.h"
#include "../../includes/game_editor.h"

static void		key_handler_2(t_doom *doom, t_event *event)
{
	if (event->scissor_lift_up == TRUE)
		scissor_lift_up(doom);
	else if (event->scissor_lift_down == TRUE)
		scissor_lift_down(doom);
}

void			key_handler(t_doom *doom, t_event *event, double dt)
{
	if (event->fall == FALSE && (event->move_pos_f == TRUE || \
		event->move_pos_b == TRUE || event->move_pos_r == TRUE ||\
		event->move_pos_l == TRUE))
		set_new_position(doom, event, dt);
	if (event->jump == TRUE && event->scissor_lift == FALSE \
		&& event->fall == FALSE)
		jump_player(doom, dt);
	if (event->fall == TRUE && event->jump == TRUE)
		get_up(doom, dt);
	if (event->step_down == TRUE && event->fall == FALSE)
		step_down(doom, dt);
	if ((event->bend == TRUE && event->scissor_lift == FALSE) || \
	(doom->player.height < doom->player.std_height +\
	doom->lib.sector[doom->i_sector].height_floor \
	&& event->fall == FALSE))
		bend_down(doom);
	if (event->bend == TRUE && event->scissor_lift == TRUE && \
		doom->player.height <= 50)
	{
		exit_scissor_lift(doom);
		event->fall = FALSE;
	}
	else
		key_handler_2(doom, event);
}

void			key_release(t_event *event, SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_w)
		event->move_pos_f = FALSE;
	else if (key->keysym.sym == SDLK_s)
		event->move_pos_b = FALSE;
	else if (key->keysym.sym == SDLK_a)
		event->move_pos_l = FALSE;
	else if (key->keysym.sym == SDLK_d)
		event->move_pos_r = FALSE;
	else if (key->keysym.sym == SDLK_UP && event->scissor_lift == TRUE)
		event->scissor_lift_up = FALSE;
	else if (key->keysym.sym == SDLK_DOWN && event->scissor_lift == TRUE)
		event->scissor_lift_down = FALSE;
	else if (key->keysym.sym == SDLK_x)
		event->bend = FALSE;
}

static void		key_press2(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_y)
		doom->menu->state = game_paused;
	else if (key->keysym.sym == SDLK_r || \
	key->keysym.sym == SDLK_e || key->keysym.sym == SDLK_t)
		key_select_and_shoot(doom, event, key);
	else if (key->keysym.sym == SDLK_SPACE)
		event->jump = TRUE;
	else if (key->keysym.sym == SDLK_x)
		event->bend = TRUE;
}

void			key_press(t_doom *doom, t_event *event,
					SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_ESCAPE)
	{
		doom->game.is_running = FALSE;
		if (doom->game.editor == TRUE)
			doom_exit_success(doom);
	}
	else if (doom->game.editor == FALSE)
	{
		if (key->keysym.sym == SDLK_w)
			event->move_pos_f = TRUE;
		else if (key->keysym.sym == SDLK_s)
			event->move_pos_b = TRUE;
		else if (key->keysym.sym == SDLK_a)
			event->move_pos_l = TRUE;
		else if (key->keysym.sym == SDLK_d)
			event->move_pos_r = TRUE;
		else if (key->keysym.sym == SDLK_UP && event->scissor_lift == TRUE)
			event->scissor_lift_up = TRUE;
		else if (key->keysym.sym == SDLK_DOWN && event->scissor_lift == TRUE)
			event->scissor_lift_down = TRUE;
		key_press2(doom, event, key);
	}
}

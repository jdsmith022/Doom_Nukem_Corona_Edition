/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_events.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:33:01 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/05 20:57:29 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	key_input(t_doom *doom, SDL_KeyboardEvent *key, double dt)
{
	if (key->keysym.sym == SDLK_ESCAPE)
		doom->is_running = FALSE;
	else if (key->keysym.sym == SDLK_w)
		position_movement_f(doom, dt);
	else if (key->keysym.sym == SDLK_s)
		position_movement_b(doom, dt);
	else if (key->keysym.sym == SDLK_a)
		position_movement_l(doom, dt);
	else if (key->keysym.sym == SDLK_d)
		position_movement_r(doom, dt);
	else if (key->keysym.sym == SDLK_UP)
		doom->player_height += 10;
	else if (key->keysym.sym == SDLK_DOWN)
		doom->player_height -= 10;
	else if (key->keysym.sym == SDLK_SPACE)
		jump_player(doom);
}

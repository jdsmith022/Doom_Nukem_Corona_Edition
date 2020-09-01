/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:38 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/01 19:19:54 by mminkjan      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/events.h"
#include "../../includes/menu.h"
#include "../../includes/font.h"
#include "../../includes/sprites.h"
#include "../../includes/audio.h"
#include "../../includes/gameplay.h"
#include "../../includes/game_editor.h"

static void	core_gameplay_loop(t_doom *doom, double dt)
{
	if (doom->game.editor == TRUE)
		open_game_editor(doom, dt);
	sprite_reset(doom);
	action_handler(doom);
	audio(doom, &doom->own_event);
}

void	sdl_poll_events(t_doom *doom, double dt)
{
	SDL_Event event;

	event = doom->event;
	doom->own_event.mouse_press = FALSE;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			doom->game.is_running = FALSE;
			if (doom->game.editor == TRUE)
				doom->game.editor = FALSE;
		}
		if (event.type == SDL_KEYDOWN)
			key_press(doom, &doom->own_event, &event.key);
		if (event.type == SDL_KEYUP)
			key_release(&doom->own_event, &event.key);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(doom, &event.button, doom->own_event);
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(doom, &event.button);
		if (event.type == SDL_MOUSEMOTION && doom->own_event.fall == FALSE)
			move_cam_direction(doom, &event.motion, dt, &doom->own_event);
	}
	key_handler(doom, &doom->own_event, dt);
}

void		doom_update(t_doom *doom, double dt)
{
	core_gameplay_loop(doom, dt);
	sdl_poll_events(doom, dt);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_update.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 21:17:35 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/05 20:56:41 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	doom_update(t_doom *doom, double dt)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom->is_running = FALSE;
		if (event.type == SDL_KEYDOWN)
			key_input(doom, &event.key, dt);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(doom, &event.button);
		if (event.type == SDL_MOUSEMOTION)
			camera_movement(doom, &event.motion, dt);
		if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(doom, &event.button);
	}
}

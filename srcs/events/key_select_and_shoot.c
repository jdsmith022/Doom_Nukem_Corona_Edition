/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_select_and_shoot.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:43 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:44:45 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/events.h"

static void	key_shopping_basket(t_doom *doom, t_event *event)
{
	event->mouse_pointer = event->mouse_pointer == TRUE ? FALSE : TRUE;
	if (event->mouse_pointer == TRUE)
	{
		event->select = FALSE;
		event->shoot = FALSE;
	}
}

void		key_select_and_shoot(t_doom *doom, t_event *event,
				SDL_KeyboardEvent *key)
{
	if (key->keysym.sym == SDLK_e)
	{
		event->select = event->select == TRUE ? FALSE : TRUE;
		if (event->select == TRUE)
		{
			event->shoot = FALSE;
			event->mouse_pointer = FALSE;
		}
	}
	else if (key->keysym.sym == SDLK_r)
	{
		event->shoot = event->shoot == TRUE ? FALSE : TRUE;
		if (event->shoot == TRUE)
		{
			event->select = FALSE;
			event->mouse_pointer = FALSE;
		}
	}
	else if (key->keysym.sym == SDLK_t)
		key_shopping_basket(doom, event);
}

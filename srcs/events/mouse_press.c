/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_press.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:52 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 18:15:12 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"
#include "../../includes/action.h"
#include "../../includes/events.h"
#include "../../includes/game_editor.h"

static void		shoot_action(t_doom *doom)
{
	if (doom->hud->sanitizer_level > 0)
	{
		doom->hud->update = sanitizer_shooting;
		doom->own_event.mist = TRUE;
		check_sprite_hit(doom);
	}
	doom->own_event.mouse_press = FALSE;
}

static void		select_action(t_doom *doom)
{
	t_sidedef poster;

	poster = doom->lib.sidedef[doom->i_sidedef];
	if (doom->own_event.select || doom->own_event.mouse_pointer)
	{
		groceries(doom);
		if (doom->own_event.groc_pickup == TRUE)
			doom->own_event.mouse_press = FALSE;
		check_sprite_hit(doom);
	}
	if (doom->own_event.groc_pickup == FALSE && \
	doom->own_event.mouse_pointer == FALSE)
	{
		if (poster.action == 4 && doom->cast.poster == light_click)
			light_switch(doom, poster);
		if (poster.action == 8 && doom->cast.poster == refill_station \
		&& poster.distance < 50.0)
			sanitizer_refill(doom);
	}
}

void			mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
		doom->own_event.mouse_press = FALSE;
}

void			mouse_press(t_doom *doom, SDL_MouseButtonEvent *button,
					t_event event)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = WIDTH / 2;
		doom->own_event.hold_y = HEIGHT / 2;
		doom->own_event.mouse_press = TRUE;
	}
	if (doom->game.editor == TRUE)
		mouse_press_game_editor(doom, button->x, button->y);
	else if (doom->own_event.shoot == TRUE)
		shoot_action(doom);
	else
		select_action(doom);
}

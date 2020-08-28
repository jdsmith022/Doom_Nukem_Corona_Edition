/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   event_settings.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:17:57 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:17:58 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"

static void		mouse_handler(t_doom *doom)
{
	SDL_Rect	rect1;
	SDL_Rect	rect2;
	SDL_Rect	rect3;

	if (doom->menu->settings == TRUE)
	{
		rect1 = doom->lib.font_lib.setting_menu_font[9].font_rect;
		setting_menu_click_event(doom, rect1);
	}
	else if (doom->menu->state == menu)
	{
		rect1 = doom->lib.font_lib.start_menu_font[2].font_rect;
		rect2 = doom->lib.font_lib.start_menu_font[4].font_rect;
		rect3 = doom->lib.font_lib.start_menu_font[5].font_rect;
		start_menu_click_event(doom, rect1, rect2, rect3);
	}
	else if (doom->menu->state == game_paused)
	{
		rect1 = doom->lib.font_lib.pause_font[1].font_rect;
		pause_click_event(doom, rect1);
	}
}

static void		key_settings(t_doom *doom, SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			doom_exit_success(doom);
		if (event.key.keysym.sym == SDLK_y)
		{
			if (doom->menu->state == game_paused)
				doom->menu->state = start_game;
		}
	}
}

void			mouse_settings(t_doom *doom)
{
	SDL_Event event;

	event = doom->event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			doom_exit_success(doom);
		if (event.type == SDL_KEYDOWN)
			key_settings(doom, event);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				doom->own_event.hold_x = event.button.x;
				doom->own_event.hold_y = event.button.y;
			}
		}
	}
	if (event.type == SDL_MOUSEBUTTONDOWN || \
	event.type == SDL_MOUSEBUTTONUP)
		mouse_handler(doom);
}

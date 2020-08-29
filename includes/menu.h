/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   menu.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 16:02:24 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 17:07:26 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENU_H
# define MENU_H

typedef	struct s_doom	t_doom;

typedef enum			e_menu_state
{
	menu,
	start_game,
	game_over,
	game_editor,
	settings,
	game_paused,
	finished,
	begin,
	start_timer
}						t_menu_state;

typedef struct			s_menu {
	int					state;
	bool				settings;
	bool				menu;
	bool				start_timer;
}						t_menu;

void					doom_start(t_doom *doom);
void					mouse_settings(t_doom *doom);
void					key_settings_menu(t_doom *doom);
void					pause_click_event(t_doom *doom, SDL_Rect rect);
void					setting_menu_click_event(t_doom *doom, SDL_Rect rect);
void					start_menu_click_event(t_doom *doom, SDL_Rect rect1,\
							SDL_Rect rect2, SDL_Rect rect3);
void					instruction_window(t_doom *doom);
void					add_score_to_sdl_text(t_doom *doom);
void					print_background(t_doom *doom, Uint32 color);
void					menus(t_doom *doom);
void					menu_print_loop(t_doom *doom);
void					print_player_sprite(t_doom *doom);

#endif
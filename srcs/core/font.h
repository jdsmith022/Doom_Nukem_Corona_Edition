/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 21:05:20 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/13 14:48:48 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <time.h>
# include "../SDL2_ttf.framework/Headers/SDL_ttf.h"

typedef	struct s_doom	t_doom;

typedef struct		s_color {
	SDL_Color		white;
	SDL_Color		black;
	SDL_Color		green;
	SDL_Color		red;
	SDL_Color		blue;
}					t_color;

typedef struct		s_font {
	SDL_Surface		*font_surface;
	SDL_Rect		font_rect;
	SDL_Color		font_color;
	uint8_t			len;
	char			*str;
}					t_font;

typedef struct		s_font_lib //refactor this into index
{
	t_color			font_color;
	t_font			*setting_menu_font;
	int				setting_font_len;
	t_font			*start_menu_font;
	int				start_font_len;
	t_font			*hud_font;
	int				hud_font_len;
	t_font			*game_editor_font;
	int				ge_font_len;
	t_font			*basket_font;
	int				basket_font_len;
	int				items_in_basket;
	t_font			*shopping_font;
	int				shopping_font_len;
	t_font			*game_over_font;
	int				game_font_len;
	t_font			*instruction_font;
	int				instruction_font_len;
	bool			walking_info;
	bool			shooting_info;
	struct timespec	timer;
}					t_font_lib;

/*font functions*/
void				save_font(t_doom *doom, int *len);
void				font_to_screen(t_doom *doom);
void				draw_font(t_doom *doom, t_font *font_lib, uint8_t len);
void				save_font_libraries(t_doom *doom);
void				set_font_colors(t_doom *doom);
void				font_to_sdl(t_doom *doom, t_font *lib, \
						char *font_style, int font_size);
void				save_game_editor_font(t_doom *doom, int *len);
void				save_hud_font(t_doom *doom, int *len);
void				save_start_menu_font(t_doom *doom, int *len);
void				save_setting_window_font(t_doom *doom, int *len);
void				save_game_over_font(t_doom *doom, int *len);
void				save_instruction_font(t_doom *doom, int *len);
void				font_timer(t_doom *doom);
void				print_vanishing_text_box(t_doom *doom,
						int start, int stop);
int					find_time_difference(t_doom *doom);

#endif

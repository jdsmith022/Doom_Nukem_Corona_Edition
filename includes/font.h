/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 21:05:20 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/12 13:07:29 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
# define FONT_H

# include <time.h>
# include "../SDL2_ttf.framework/Headers/SDL_ttf.h"

typedef	struct s_doom	t_doom;

typedef struct		s_limit	{
	int				x;
	int				y;
}					t_limit;

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

typedef struct		s_bools
{
	bool			walking_info;
	bool			walking_text;
	bool			start_sector;
	bool			text;
}					t_bools;

typedef struct		s_font_lib
{
	t_color			font_color;
	t_font			*setting_menu_font;
	t_bools			bools;
	TTF_Font		*font_30;
	TTF_Font		*font_22;
	TTF_Font		*font_20;
	TTF_Font		*font_18;
	t_limit			limit_x;
	t_limit			limit_y;
	int				setting_font_len;
	t_font			*start_menu_font;
	int				start_font_len;
	t_font			*hud_font;
	int				hud_font_len;
	t_font			*game_editor_font;
	int				ge_font_len;
	t_font			*game_over_font;
	int				game_font_len;
	t_font			*instruction_font;
	int				instruction_font_len;
	t_font			*pause_font;
	int				pause_font_len;
	t_font			*finished_font;
	int				finished_font_len;
	struct timespec	timer;
}					t_font_lib;

/*font functions*/
void				save_font(t_doom *doom, int *len);
void				font_to_screen(t_doom *doom);
void				save_font_libraries(t_doom *doom);
void				set_font_colors(t_doom *doom);
void				set_font_style(t_doom *doom);
void				font_to_sdl(t_doom *doom, t_font *lib, \
						TTF_Font *font);
void				save_game_editor_font(t_doom *doom, int *len);
void				save_hud_font(t_doom *doom, int *len);
void				save_start_menu_font(t_doom *doom, int *len);
void				save_setting_window_font(t_doom *doom, int *len);
void				save_game_over_font(t_doom *doom, int *len);
void				save_instruction_font(t_doom *doom, int *len);
void				save_pause_font(t_doom *doom, int *len);
void				font_timer(t_doom *doom);
void				print_vanishing_text_box(t_doom *doom,
						int start, int stop);
void				set_background_coords_top(t_doom *doom);
void				set_background_coords_middle_small(t_doom *doom);
void				set_background_coords_middle_large(t_doom *doom);

#endif

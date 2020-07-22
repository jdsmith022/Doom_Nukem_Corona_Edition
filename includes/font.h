/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 21:05:20 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/22 21:17:16 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
#define FONT_H

# include "../SDL2_ttf.framework/Headers/SDL_ttf.h"

typedef struct   s_doom    t_doom;

typedef struct		s_color {
	SDL_Color		white;
	SDL_Color		black;
	SDL_Color		green;
	SDL_Color		red;
}					t_color;

typedef struct		s_font {
	SDL_Surface		*font_surface;
	SDL_Rect		font_rect;
	SDL_Color		font_color;
	uint8_t			len;
	char			*str;
}					t_font;

/*font functions*/
void				save_font(t_doom *doom, int *len);
void        		font_to_screen(t_doom *doom);
void	            save_font_libraries(t_doom *doom);
void				set_font_colors(t_doom *doom);
void	            font_to_surface(t_doom *doom, t_font *lib, uint8_t len);
void				save_game_editor_font(t_doom *doom, int *len);
#endif
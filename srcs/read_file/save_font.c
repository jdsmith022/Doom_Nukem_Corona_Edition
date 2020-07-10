/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: JessicaSmith <JessicaSmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 15:21:36 by JessicaSmit   #+#    #+#                 */
/*   Updated: 2020/07/10 18:57:43 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void			font_init(t_doom *doom)
{
	TTF_Font	*font;
	char		*string;
	SDL_Color	font_color;
	SDL_Rect	font_rect;

	TTF_Init();
	font = TTF_OpenFont("text/amatic/AmaticSC-Regular.tff", 12);
	string = "Fuck yeah font!";
	doom->lib.font_color[0].r = 255;
	doom->lib.font_color[0].g = 255;
	doom->lib.font_color[0].b = 255;
	doom->lib.font_rect[0].x = 300;
	doom->lib.font_rect[0].y = 300;
	doom->lib.font_lib[0] = TTF_RenderText_Solid(font, string, font_color);
}

static SDL_Surface	**string_into_surface(t_doom *doom, SDL_Surface **lib)
{
	int			len;

	len = 1;
	lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	font_init(doom);
	return (lib);
}

SDL_Surface		**save_font(t_doom *doom)
{
	SDL_Surface **lib;

	string_into_surface(doom, lib);
	doom->lib.n_fonts = 1;
	return (lib);
}

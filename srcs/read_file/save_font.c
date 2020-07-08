/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: JessicaSmith <JessicaSmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 15:21:36 by JessicaSmit   #+#    #+#                 */
/*   Updated: 2020/07/08 16:25:22 by JessicaSmit   ########   odam.nl         */
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
	font_color.r = 255;
	font_color.g = 255;
	font_color.b = 255;
	font_rect.x = 300;
	font_rect.y = 300;
	doom->lib.font_lib[0] = TTF_RenderText_Solid(font, string, font_color);
}

static SDL_Surface	**string_into_surface(t_doom *doom)
{
	SDL_Surface **lib;
	int			len;

	len = 1;
	lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	font_init(doom);
	return (lib);
}

void		save_font(t_doom *doom)
{
	doom->lib.font_lib = string_into_surface(doom);
	doom->lib.n_fonts = 1;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_font.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: JessicaSmith <JessicaSmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 15:21:36 by JessicaSmit   #+#    #+#                 */
/*   Updated: 2020/07/14 11:55:46 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	font_save_to_surface(t_doom *doom)
{
	TTF_Font	*font;
	char		*string;
	SDL_Color	font_color;
	SDL_Surface	*font_surface;

	TTF_Init();
	font = TTF_OpenFont("text/amatic/AmaticSC-Regular.tff", 14);
	string = "Fuck yeah font!";
	font_color.r = 255;
	font_color.g = 255;
	font_color.b = 255;
	doom->lib.font_lib[0].font_rect.x = 300;
	doom->lib.font_lib[0].font_rect.y = 300;
	font_surface = (SDL_Surface*)ft_memalloc(sizeof(SDL_Surface) * doom->lib.n_fonts);
	if (font_surface == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	printf("x,y: %d, %d\n", doom->lib.font_lib[0].font_rect.x, doom->lib.font_lib[0].font_rect.y);
	printf("%s\n", font_surface->pixels);
	font_surface = TTF_RenderText_Solid(font, string, font_color);
	printf("boom\n");
	if (font_surface == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.font_lib[0].font_surface = font_surface;
}

static void	malloc_for_font_surfaces(t_doom *doom)
{
	SDL_Surface *lib;

	lib = doom->lib.font_lib->font_surface;
	lib = (SDL_Surface*)ft_memalloc(sizeof(SDL_Surface) * doom->lib.n_fonts);
	if (lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.font_lib->font_surface = lib;
	font_save_to_surface(doom);
}

void		save_font(t_doom *doom)
{
	t_font		*font_lib;

	doom->lib.n_fonts = 1;
	font_lib = doom->lib.font_lib;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * doom->lib.n_fonts);
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.font_lib = font_lib;
	malloc_for_font_surfaces(doom);
}

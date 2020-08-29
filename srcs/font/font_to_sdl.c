/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_to_sdl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 21:23:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 10:35:07 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	single_font_to_sdl(t_doom *doom, t_font lib, TTF_Font *font)
{
	SDL_Surface	*font_surface;

	TTF_Init();
	font_surface =
		TTF_RenderText_Solid(font, lib.str, lib.font_color);
	lib.font_surface = font_surface;
	SDL_BlitSurface(lib.font_surface, NULL, doom->surface, &lib.font_rect);
	SDL_FreeSurface(font_surface);
}

void	font_to_sdl(t_doom *doom, t_font *lib, TTF_Font *font)
{
	SDL_Surface	*font_surface;
	size_t		index;
	uint8_t		len;

	index = 0;
	len = lib[index].len;
	TTF_Init();
	while (index < len)
	{
		font_surface =
			TTF_RenderText_Solid(font, lib[index].str, lib[index].font_color);
		lib[index].font_surface = font_surface;
		index++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_to_sdl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 20:03:17 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/26 17:48:46 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	font_to_sdl(t_doom *doom, t_font *lib, char *font_path,
			int font_size)
{
	TTF_Font	*font;
	SDL_Surface	*font_surface;
	size_t		index;
	uint8_t		len;

	index = 0;
	len = lib[index].len;
	TTF_Init();
	font = TTF_OpenFont(font_path, font_size);
	while (index < len)
	{
		font_surface =
			TTF_RenderText_Solid(font, lib[index].str, lib[index].font_color);
		if (font_surface == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		lib[index].font_surface = font_surface;
		index++;
	}
}

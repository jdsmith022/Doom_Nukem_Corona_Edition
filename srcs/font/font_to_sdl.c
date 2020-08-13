/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_to_sdl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 20:03:17 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/12 09:28:09 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

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
		if (font_surface == NULL)
			doom_exit_failure(doom, "error: font to surface");
		lib[index].font_surface = font_surface;
		index++;
	}
}

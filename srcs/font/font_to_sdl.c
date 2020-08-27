/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_to_sdl.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 21:23:20 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/27 22:33:23 by jesmith       ########   odam.nl         */
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
		lib[index].font_surface = font_surface;
		index++;
	}
	free(font_surface);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_to_window.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/14 12:43:48 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		draw_font(t_doom *doom)
{
	Uint32	index;
	int		total_fonts;

	index = 0;
	total_fonts = doom->lib.n_fonts;
	while (index < total_fonts)
	{
		// // SDL_BlitSurface(doom->lib.font_lib[index].font_surface, NULL,\
		// 	doom->surface, &doom->lib.font_lib[index].font_rect);
		// // SDL_Flip(doom->surface);
		index++;
	}
}

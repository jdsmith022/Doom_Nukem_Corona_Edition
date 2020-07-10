/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_to_window.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/10 18:53:21 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		draw_text(t_doom *doom)
{
	Uint32	index;
	int		total_fonts;

	index = 0;
	total_fonts = doom->lib.n_fonts;
	while (index < total_fonts)
	{
		SDL_BlitSurface(doom->lib.font_lib[index], NULL,\
			doom->surface, &doom->lib.font_rect[index]);
		// SDL_Flip(doom->surface);
		index++;
	}
}

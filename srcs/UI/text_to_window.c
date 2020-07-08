/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_to_window.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/03 15:16:05 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/08 15:54:42 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void fontInit(t_doom *doom)
{


void        draw_text(t_doom *doom)
{
    Uint32  index;
    int     total_fonts;

	index = 0;
    total_fonts = doom->lib.n_fonts;
	while (index < total_fonts)
	{
		SDL_BlitSurface(fontSurface, NULL, screen, &fontRect);
        SDL_Flip(screen);
		index++;
	}
}

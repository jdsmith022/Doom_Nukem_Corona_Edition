/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_background.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:18:26 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:18:27 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		print_background(t_doom *doom, Uint32 color)
{
	Uint32	*pixels;
	int		x;
	int		y;

	pixels = doom->surface->pixels;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (x >= 0 && x <= WIDTH && y >= 0 && y <= HEIGHT)
				pixels[(y * WIDTH + x)] = color;
			y++;
		}
		x++;
	}
}

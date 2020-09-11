/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_portal_pixel.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/06 21:46:23 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 21:46:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

void			put_portal_pixel(t_doom *doom, t_point pixel,
					int tint, int mask)
{
	Uint32	*pixels;
	Uint32	color;

	if (pixel.x >= 0 && pixel.x < WIDTH && pixel.y >= 0 && pixel.y < HEIGHT)
	{
		pixels = doom->surface->pixels;
		color = pixels[((int)pixel.y * WIDTH) + (int)pixel.x];
		if (tint != 0)
			add_tint_to_color(&color, tint, mask);
		pixels[((int)pixel.y * WIDTH) + (int)pixel.x] = color;
	}
}

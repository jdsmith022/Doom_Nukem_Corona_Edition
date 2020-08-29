/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bmp_to_sdl.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 11:41:59 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/27 22:00:28 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/read.h"

void			save_bpm_to_sdl(t_doom *doom, t_bmp *images,
						SDL_Surface **lib, int index)
{
	lib[index] = SDL_CreateRGBSurface(0, \
		images->info.width, images->info.height,\
		24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (lib[index] == NULL)
		bmp_safe_exit(doom, images);
	ft_memcpy(lib[index]->pixels, images->pixels,\
		(images->info.img_size));
}

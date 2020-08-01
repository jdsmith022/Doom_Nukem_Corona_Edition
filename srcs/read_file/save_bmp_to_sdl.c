/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_bmp_to_sdl.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 11:41:59 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/01 13:22:13 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			save_bpm_to_sdl(t_doom *doom, t_bmp *images,
						SDL_Surface **lib, int index)
{
	lib[index] = SDL_CreateRGBSurface(0, \
		images[index].info.width, images[index].info.height,\
		24, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	if (lib[index] == NULL)
	{
		doom_exit_lib_failure(images, MALLOC_ERR);
		doom_exit_failure(doom, MALLOC_ERR);
	}
	ft_memcpy(lib[index]->pixels, images[index].pixels,\
		(images[index].info.img_size));
}

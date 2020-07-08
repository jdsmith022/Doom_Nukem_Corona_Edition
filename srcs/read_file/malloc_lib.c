
/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lib_malloc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 16:05:46 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/05 16:09:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

t_bmp			*malloc_images_lib(int len)
{
	t_bmp *temp_images;

	temp_images = (t_bmp *)ft_memalloc(sizeof(t_bmp) * len);
	if (temp_images == NULL)
		doom_exit_failure(NULL, MALLOC_ERR);
	return (temp_images);
}

SDL_Surface		**malloc_sdl_lib(t_bmp *images, int len)
{
	SDL_Surface **temp_lib;

	temp_lib = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * len);
	if (temp_lib == NULL)
		doom_exit_lib_failure(images, MALLOC_ERR);
	return (temp_lib);
}

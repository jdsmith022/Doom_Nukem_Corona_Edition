/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sdl_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 14:21:26 by Malou         #+#    #+#                 */
/*   Updated: 2020/05/27 15:29:05 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

int		sdl_init(t_doom *doom)
{
	//SDL_Surface	*resized_surface;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) // check what to init
		return (1);
	doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	if (doom->window == NULL)
		return (1);
	doom->surface = SDL_GetWindowSurface(doom->window);
	if (doom->surface == NULL)
		return (1);
	//resized_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	//if (resized_surface == NULL)
	//	return (1);
	return (0);
}

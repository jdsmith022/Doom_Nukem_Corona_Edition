/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sdl_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/27 14:21:26 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/11 13:15:17 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

int		sdl_init(t_doom *doom)
{
	//SDL_Surface	*resized_surface;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) // check what to init
		return (1);
	doom->window = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,\
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	SDL_SetWindowInputFocus(doom->window);
	//printf("%s\n", SDL_GetError());
	if (doom->window == NULL)
		return (1);
	doom->surface = SDL_GetWindowSurface(doom->window);
	if (doom->surface == NULL)
		return (1);
	//resized_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	//if (resized_surface == NULL)
	//	return (1);
	SDL_WarpMouseInWindow(doom->window, WIDTH / 2, HEIGHT / 2);
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_CaptureMouse(SDL_TRUE);
	//printf("%s\n", SDL_GetError());s
	return (0);
}

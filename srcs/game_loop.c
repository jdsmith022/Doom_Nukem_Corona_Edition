/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 14:56:13 by Malou          #+#    #+#                */
/*   Updated: 2020/04/01 21:48:21 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

//void	draw_lines(t_doom *doom)
//{
//	SDL_Point points[5] = {
//		{0, 0}, 
//		{0, 100}, 
//		{100, 100}, 
//		{100, 0},
//		{0, 0}};


//	SDL_SetRenderDrawColor(doom->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
//	SDL_RenderDrawLines(doom->renderer, points, 5);
//	SDL_RenderPresent(doom->renderer);
//}

void	doom_gui(t_doom *doom)
{
	(void)doom;
}

void 	doom_sound(t_doom *doom)
{
	(void)doom;
}

void	game_loop(t_doom *doom)
{
	while (doom->esc == 0)
	{
		doom_render(doom);
		//draw_lines(doom);
		doom_input(doom);
		doom_sound(doom);
		doom_gui(doom);
		SDL_UpdateWindowSurface(doom->window);
		ft_bzero(doom->surface->pixels, sizeof(doom->surface->pixels));
    }
}
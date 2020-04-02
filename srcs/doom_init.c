/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:45:11 by Malou          #+#    #+#                */
/*   Updated: 2020/04/02 21:29:23 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	set_lines(t_doom *doom)
{
	doom->sidedef[0].start.x = 0;
	doom->sidedef[0].start.y = 0;
	doom->sidedef[0].end.x = 0;
	doom->sidedef[0].end.y = 1000;
	doom->sidedef[0].sector = 2;
	doom->sidedef[0].opp = NULL;
	doom->sidedef[0].opp_sector = 0;

	doom->sidedef[1].start.x = 0;
	doom->sidedef[1].start.y = 1000;
	doom->sidedef[1].end.x = 1000;
	doom->sidedef[1].end.y = 1000;
	doom->sidedef[1].sector = 2;
	doom->sidedef[1].opp = NULL;
	doom->sidedef[1].opp_sector = 0;

	doom->sidedef[2].start.x = 1000;
	doom->sidedef[2].start.y = 1000;
	doom->sidedef[2].end.x = 1000;
	doom->sidedef[2].end.y = 0;
	doom->sidedef[2].sector = 1;
	doom->sidedef[2].opp = NULL;
	doom->sidedef[2].opp_sector = 0;

	doom->sidedef[3].start.x = 1000;
	doom->sidedef[3].start.y = 0;
	doom->sidedef[3].end.x = 0;
	doom->sidedef[3].end.y = 0;
	doom->sidedef[3].sector = 1;
	doom->sidedef[3].opp = NULL;
	doom->sidedef[3].opp_sector = 0;
	
	doom->sidedef[4].start.x = 0;
	doom->sidedef[4].start.y = 0;
	doom->sidedef[4].end.x = 1000;
	doom->sidedef[4].end.y = 1000;
	doom->sidedef[4].sector = 1;
	doom->sidedef[4].opp = &doom->sidedef[5];
	doom->sidedef[4].opp_sector = 2;

	doom->sidedef[5].start.x = 0;
	doom->sidedef[5].start.y = 0;
	doom->sidedef[5].end.x = 1000;
	doom->sidedef[5].end.y = 1000;
	doom->sidedef[5].sector = 2;
	doom->sidedef[5].opp = &doom->sidedef[4];
	doom->sidedef[5].opp_sector = 2;
}

void doom_init(t_doom *doom)
{
	SDL_Init(SDL_INIT_VIDEO);
	doom->window = SDL_CreateWindow("Doom", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
	doom->surface = SDL_GetWindowSurface(doom->window);
	set_lines(doom);
	doom->esc = 0;
	doom->dir_angle = 90;
	doom->ray_adjacent = FOV / WIDTH;
	doom->pos.x = 300;
	doom->pos.y = 500;
	doom->max_ray = 10000;
	doom->curr_sector = 0;
	doom->sector[0].height_ceiling = 64;
	doom->sector[0].height_floor = 0;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
}
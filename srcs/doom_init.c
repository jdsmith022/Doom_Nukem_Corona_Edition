/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:45:11 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/06 15:03:04 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	set_lines(t_doom *doom)
{
	doom->sector[0].sidedef[0].start.x = 0;
	doom->sector[0].sidedef[0].start.y = 0;
	doom->sector[0].sidedef[0].end.x = 200;
	doom->sector[0].sidedef[0].end.y = 0;
	doom->sector[0].sidedef[0].sector = 0;
	doom->sector[0].sidedef[0].opp = NULL;
	doom->sector[0].sidedef[0].opp_sector = -1;

	doom->sector[0].sidedef[1].start.x = 200;
	doom->sector[0].sidedef[1].start.y = 0;
	doom->sector[0].sidedef[1].end.x = 200;
	doom->sector[0].sidedef[1].end.y = 250;
	doom->sector[0].sidedef[1].sector = 0;
	doom->sector[0].sidedef[1].opp = &doom->sector[1].sidedef[3];
	doom->sector[0].sidedef[1].opp_sector = 1;

	doom->sector[0].sidedef[2].start.x = 200;
	doom->sector[0].sidedef[2].start.y = 250;
	doom->sector[0].sidedef[2].end.x = 200;
	doom->sector[0].sidedef[2].end.y = 500;
	doom->sector[0].sidedef[2].sector = 0;
	doom->sector[0].sidedef[2].opp = NULL;
	doom->sector[0].sidedef[2].opp_sector = -1;
	
	doom->sector[0].sidedef[3].start.x = 200;
	doom->sector[0].sidedef[3].start.y = 500;
	doom->sector[0].sidedef[3].end.x = 0;
	doom->sector[0].sidedef[3].end.y = 500;
	doom->sector[0].sidedef[3].sector = 0;
	doom->sector[0].sidedef[3].opp = NULL;
	doom->sector[0].sidedef[3].opp_sector = -1;

	doom->sector[0].sidedef[4].start.x = 0;
	doom->sector[0].sidedef[4].start.y = 500;
	doom->sector[0].sidedef[4].end.x = 0;
	doom->sector[0].sidedef[4].end.y = 0;
	doom->sector[0].sidedef[4].sector = 0;
	doom->sector[0].sidedef[4].opp = NULL;
	doom->sector[0].sidedef[4].opp_sector = -1;
	
	doom->sector[1].sidedef[0].start.x = 200;
	doom->sector[1].sidedef[0].start.y = 0;
	doom->sector[1].sidedef[0].end.x = 300;
	doom->sector[1].sidedef[0].end.y = 0;
	doom->sector[1].sidedef[0].sector = 1;
	doom->sector[1].sidedef[0].opp = NULL;
	doom->sector[1].sidedef[0].opp_sector = -1;

	doom->sector[1].sidedef[1].start.x = 300;
	doom->sector[1].sidedef[1].start.y = 0;
	doom->sector[1].sidedef[1].end.x = 300;
	doom->sector[1].sidedef[1].end.y = 250;
	doom->sector[1].sidedef[1].sector = 1;
	doom->sector[1].sidedef[1].opp = &doom->sector[2].sidedef[3];
	doom->sector[1].sidedef[1].opp_sector = 2;

	doom->sector[1].sidedef[2].start.x = 300;
	doom->sector[1].sidedef[2].start.y = 250;
	doom->sector[1].sidedef[2].end.x = 200;
	doom->sector[1].sidedef[2].end.y = 250;
	doom->sector[1].sidedef[2].sector = 1;
	doom->sector[1].sidedef[2].opp = NULL;
	doom->sector[1].sidedef[2].opp_sector = -1;

	doom->sector[1].sidedef[3].start.x = 200;
	doom->sector[1].sidedef[3].start.y = 250;
	doom->sector[1].sidedef[3].end.x = 200;
	doom->sector[1].sidedef[3].end.y = 0;
	doom->sector[1].sidedef[3].sector = 1;
	doom->sector[1].sidedef[3].opp = &doom->sector[0].sidedef[1];
	doom->sector[1].sidedef[3].opp_sector = 0;

	doom->sector[2].sidedef[0].start.x = 300;
	doom->sector[2].sidedef[0].start.y = 0;
	doom->sector[2].sidedef[0].end.x = 500;
	doom->sector[2].sidedef[0].end.y = 0;
	doom->sector[2].sidedef[0].sector = 2;
	doom->sector[2].sidedef[0].opp = NULL;
	doom->sector[2].sidedef[0].opp_sector = -1;

	doom->sector[2].sidedef[1].start.x = 500;
	doom->sector[2].sidedef[1].start.y = 0;
	doom->sector[2].sidedef[1].end.x = 500;
	doom->sector[2].sidedef[1].end.y = 250;
	doom->sector[2].sidedef[1].sector = 2;
	doom->sector[2].sidedef[1].opp = NULL;
	doom->sector[2].sidedef[1].opp_sector = -1;

	doom->sector[2].sidedef[2].start.x = 500;
	doom->sector[2].sidedef[2].start.y = 250;
	doom->sector[2].sidedef[2].end.x = 300;
	doom->sector[2].sidedef[2].end.y = 250;
	doom->sector[2].sidedef[2].sector = 2;
	doom->sector[2].sidedef[2].opp = NULL;
	doom->sector[2].sidedef[2].opp_sector = -1;

	doom->sector[2].sidedef[3].start.x = 300;
	doom->sector[2].sidedef[3].start.y = 250;
	doom->sector[2].sidedef[3].end.x = 300;
	doom->sector[2].sidedef[3].end.y = 0;
	doom->sector[2].sidedef[3].sector = 2;
	doom->sector[2].sidedef[3].opp = &doom->sector[1].sidedef[1];
	doom->sector[2].sidedef[3].opp_sector = 1;
}

void doom_init(t_doom *doom)
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0) // check what to init
	{
		doom->window = SDL_CreateWindow("Doom", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);
			if (doom->window == NULL) 
		    doom_exit_failure(doom, MALLOC_ERR);
		doom->surface = SDL_GetWindowSurface(doom->window);
		if (doom->surface == NULL) 
		    doom_exit_failure(doom, MALLOC_ERR);
	}
	else
		doom_exit_failure(doom, INIT_ERR);
	set_lines(doom);
	doom->esc = 0;
	doom->dir_angle = 180;
	doom->ray_adjacent = FOV / WIDTH;
	doom->pos.x = 50;
	doom->pos.y = 100;
	doom->max_ray = 10000;
	doom->curr_sector = 0;
	doom->sector[0].height_ceiling = 64;
	doom->sector[0].height_floor = 0;
	doom->sector[0].n_sidedefs = 5;
	doom->sector[1].height_ceiling = 64;
	doom->sector[1].height_floor = 20;
	doom->sector[1].n_sidedefs = 4;
	doom->sector[2].height_ceiling = 64;
	doom->sector[2].height_floor = 40;
	doom->sector[2].n_sidedefs = 4;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
}
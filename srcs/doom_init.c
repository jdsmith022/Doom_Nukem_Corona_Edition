/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/01 13:45:11 by Malou         #+#    #+#                 */
/*   Updated: 2020/04/14 11:28:10 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void	set_lines(t_sidedef *sidedef)
{
	sidedef[0].start.x = 0;
	sidedef[0].start.y = 0;
	sidedef[0].end.x = 200;
	sidedef[0].end.y = 0;
	sidedef[0].sector = 0;
	sidedef[0].opp_sidedef = -1;
	sidedef[0].opp_sector = -1;

	sidedef[1].start.x = 200;
	sidedef[1].start.y = 0;
	sidedef[1].end.x = 200;
	sidedef[1].end.y = 250;
	sidedef[1].sector = 0;
	sidedef[1].opp_sidedef = 8;
	sidedef[1].opp_sector = 1;

	sidedef[2].start.x = 200;
	sidedef[2].start.y = 250;
	sidedef[2].end.x = 200;
	sidedef[2].end.y = 500;
	sidedef[2].sector = 0;
	sidedef[2].opp_sidedef = -1;
	sidedef[2].opp_sector = -1;
	
	sidedef[3].start.x = 200;
	sidedef[3].start.y = 500;
	sidedef[3].end.x = 0;
	sidedef[3].end.y = 500;
	sidedef[3].sector = 0;
	sidedef[3].opp_sidedef = -1;
	sidedef[3].opp_sector = -1;

	sidedef[4].start.x = 0;
	sidedef[4].start.y = 500;
	sidedef[4].end.x = 0;
	sidedef[4].end.y = 0;
	sidedef[4].sector = 0;
	sidedef[4].opp_sidedef = -1;
	sidedef[4].opp_sector = -1;
	
	sidedef[5].start.x = 200;
	sidedef[5].start.y = 0;
	sidedef[5].end.x = 300;
	sidedef[5].end.y = 0;
	sidedef[5].sector = 1;
	sidedef[5].opp_sidedef = -1;
	sidedef[5].opp_sector = -1;

	sidedef[6].start.x = 300;
	sidedef[6].start.y = 0;
	sidedef[6].end.x = 300;
	sidedef[6].end.y = 250;
	sidedef[6].sector = 1;
	sidedef[6].opp_sidedef = 12;
	sidedef[6].opp_sector = 2;

	sidedef[7].start.x = 300;
	sidedef[7].start.y = 250;
	sidedef[7].end.x = 200;
	sidedef[7].end.y = 250;
	sidedef[7].sector = 1;
	sidedef[7].opp_sidedef = -1;
	sidedef[7].opp_sector = -1;

	sidedef[8].start.x = 200;
	sidedef[8].start.y = 250;
	sidedef[8].end.x = 200;
	sidedef[8].end.y = 0;
	sidedef[8].sector = 1;
	sidedef[8].opp_sidedef = 1;
	sidedef[8].opp_sector = 0;

	sidedef[9].start.x = 300;
	sidedef[9].start.y = 0;
	sidedef[9].end.x = 500;
	sidedef[9].end.y = 0;
	sidedef[9].sector = 2;
	sidedef[9].opp_sidedef = -1;
	sidedef[9].opp_sector = -1;

	sidedef[10].start.x = 500;
	sidedef[10].start.y = 0;
	sidedef[10].end.x = 500;
	sidedef[10].end.y = 250;
	sidedef[10].sector = 2;
	sidedef[10].opp_sidedef = -1;
	sidedef[10].opp_sector = -1;

	sidedef[11].start.x = 500;
	sidedef[11].start.y = 250;
	sidedef[11].end.x = 300;
	sidedef[11].end.y = 250;
	sidedef[11].sector = 2;
	sidedef[11].opp_sidedef = -1;
	sidedef[11].opp_sector = -1;

	sidedef[12].start.x = 300;
	sidedef[12].start.y = 250;
	sidedef[12].end.x = 300;
	sidedef[12].end.y = 0;
	sidedef[12].sector = 2;
	sidedef[12].opp_sidedef = 6;
	sidedef[12].opp_sector = 1;
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
	set_lines(doom->sidedef);
	doom->esc = 0;
	doom->dir_angle = 180;
	doom->ray_adjacent = FOV / WIDTH;
	doom->pos.x = 50;
	doom->pos.y = 100;
	doom->max_ray = 10000;
	doom->i_sector = 0;
	doom->sector[0].height_ceiling = 64;
	doom->sector[0].height_floor = 0;
	doom->sector[0].i_sidedefs = 0;
	doom->sector[0].n_sidedefs = 5;
	doom->sector[1].height_ceiling = 64;
	doom->sector[1].height_floor = 20;
	doom->sector[1].i_sidedefs = 5;
	doom->sector[1].n_sidedefs = 4;
	doom->sector[2].height_ceiling = 64;
	doom->sector[2].height_floor = 40;
	doom->sector[2].i_sidedefs = 9;
	doom->sector[2].n_sidedefs = 4;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
}
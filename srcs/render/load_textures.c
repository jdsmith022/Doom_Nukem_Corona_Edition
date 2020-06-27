/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 17:07:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/06/16 17:53:20 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include <sys/stat.h>

void		load_bmp(t_doom *doom)
{
	size_t nb_textures; //put into struct -> info taken while reading maps

	nb_textures = 2;
	doom->textures = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * nb_textures); // allocating space for struct
	if (doom->textures == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->textures[0] = SDL_LoadBMP("./textures/WALL03_1.bmp");
	doom->textures[1] = SDL_LoadBMP("./textures/WALL03_7.bmp");
}

void		load_textures (t_doom *doom)
{
	load_bmp(doom);
}
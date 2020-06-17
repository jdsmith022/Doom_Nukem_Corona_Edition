/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 17:07:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/06/17 13:06:59 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include <sys/stat.h>

void		load_textures (t_doom *doom)
{

	size_t nb_textures;
	size_t index;

	nb_textures = 2;
	index = 0;
	doom->textures = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * nb_textures); // allocating space for struct
	if (doom->textures == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->textures[0] = SDL_LoadBMP("./textures/WALL03_1.bmp");
	doom->textures[1] = SDL_LoadBMP("./textures/WALL03_7.bmp");
}

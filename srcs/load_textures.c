/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 17:07:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/04/28 15:04:52 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		load_png(t_doom *doom, int fd)
{

	size_t nb_textures; //put into struct -> info taken while reading maps
	int w;
	int h;
	size_t index;

	nb_textures = 1;
	index = 0;
	doom->textures = (SDL_Surface**)ft_memalloc(sizeof(SDL_Surface*) * nb_textures); // allocating space for struct
	if (doom->textures == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	while (index < nb_textures)
	{
		if (read(fd, &w, sizeof(int)) < 0 || read(fd, &h, sizeof(int) < 0))
			doom_exit_failure(doom, MALLOC_ERR);
		doom->textures[index] = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_ARGB8888);
		if (doom->textures[index] == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		if ((read(fd, doom->textures[index]->pixels, w * h * 4)) < 0)
			doom_exit_failure(doom, MALLOC_ERR);
		index++;
	}
}

void		load_textures (t_doom *doom)
{
	int fd;

	fd = open("./textures/WALL03_1.bmp", O_RDONLY);
	if (fd < 0)
		doom_exit_failure(doom, MALLOC_ERR);
	load_png(doom, fd);
}
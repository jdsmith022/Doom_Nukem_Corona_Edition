/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 17:07:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/05/03 10:40:47 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		load_bmp(t_doom *doom, int fd)
{

	size_t nb_textures; //put into struct -> info taken while reading maps
	int w;
	int h;
	size_t index;

	nb_textures = 1;
	index = 0;
	doom->textures = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * nb_textures); // allocating space for struct
	if (doom->textures == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	// doom->textures[index] = SDL_LoadBMP("./textures/WALL03_1.bmp");
	while (index < nb_textures)
	{
		if (read(fd, &w, sizeof(int)) < 0 || read(fd, &h, sizeof(int) < 0))
			doom_exit_failure(doom, MALLOC_ERR);
		h = 1;
		doom->textures[index] = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
		if (doom->textures[index] == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		if ((read(fd, doom->textures[index]->pixels, (size_t)w * h * 4)) < 0)
			doom_exit_failure(doom, READ_ERR);
		if (doom->textures[index]->pixels == NULL)
			doom_exit_failure(doom, WALL_ERR);
		index++;
	}
}

void		load_textures (t_doom *doom)
{
	int fd;

	fd = open("./textures/WALL03_1.bmp", O_RDONLY);
	if (fd < 0)
		doom_exit_failure(doom, MALLOC_ERR);
	lseek(fd, 0, SEEK_SET);
	load_bmp(doom, fd);
	close(fd);

}

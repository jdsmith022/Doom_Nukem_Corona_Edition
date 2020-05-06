/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   load_textures.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 17:07:11 by jesmith       #+#    #+#                 */
/*   Updated: 2020/05/06 17:03:53 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"
#include <sys/stat.h>

void		load_bmp(t_doom *doom, FILE *fd)
{

	size_t nb_textures; //put into struct -> info taken while reading maps
	size_t w = 0;
	size_t h = 0;
	size_t index;
	size_t	filesize;

	// (void)fd;
	nb_textures = 1;
	index = 0;
	doom->textures = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * nb_textures); // allocating space for struct
	if (doom->textures == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	// doom->textures[index] = SDL_LoadBMP("./textures/WALL03_1.bmp");
	while (index < nb_textures)
	{
		if (fread(&w, sizeof(int), 1, fd) < 0)
			doom_exit_failure(doom, MALLOC_ERR);
		// fd = lseek(fd, 0, SEEK_SET);
		if (fread(&h, sizeof(int), 1, fd) < 0)
			doom_exit_failure(doom, MALLOC_ERR);
		if (h == 0)
			h = 1;
		doom->textures[index] = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, SDL_PIXELFORMAT_ARGB8888);
		if (doom->textures[index] == NULL)
			doom_exit_failure(doom, MALLOC_ERR);
		filesize = w * h * 4;
		// filesize = lseek(fd, 0, SEEK_END) * 4;
		printf("%zu\n", filesize);
		if ((fread(doom->textures[index]->pixels, filesize, 1, fd)) < 0)
			doom_exit_failure(doom, READ_ERR);
		if (doom->textures[index]->pixels == NULL) // ERROR HERE...pixels is empty? why?
			doom_exit_failure(doom, WALL_ERR);
		printf("%s\n", doom->textures[index]->pixels);
		index++;
	}
}

void		load_textures (t_doom *doom)
{
	// int fd;
	FILE *fd;

	fd = fopen("./textures/WALL03_1.bmp", "r");
	if (fd < 0)
		doom_exit_failure(doom, MALLOC_ERR);
	// lseek(fd, 0, SEEK_SET);
	load_bmp(doom, fd);
	fclose(fd);

}

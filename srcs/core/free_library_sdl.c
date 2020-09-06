/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_library_sdl.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:29 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 12:03:10 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void		free_sld_libs(SDL_Surface **lib, int len)
{
	size_t index;

	index = 0;
	while (index < len)
	{
		ft_bzero(lib[index], sizeof(lib[index]));
		free(lib[index]);
		index++;
	}
	free(lib);
}

void			free_sdl_lib(t_doom *doom)
{
	SDL_Surface	**lib;
	int			len;

	if (doom->lib.tex_lib)
	{
		lib = doom->lib.tex_lib;
		len = doom->lib.len_tex_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.obj_lib)
	{
		lib = doom->lib.obj_lib;
		len = doom->lib.len_obj_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.sky_lib)
	{
		lib = doom->lib.sky_lib;
		len = doom->lib.len_sky_lib;
		free_sld_libs(lib, len);
	}
	if (doom->lib.player_lib)
	{
		lib = doom->lib.player_lib;
		len = doom->lib.len_player_lib;
		free_sld_libs(lib, len);
	}
}

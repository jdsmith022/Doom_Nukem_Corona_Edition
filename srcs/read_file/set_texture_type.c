/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture_type.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/25 10:44:38 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/27 20:59:12 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/textures.h"
#include "../../includes/read.h"

static bool	is_of_type(const char *path_loaded, t_grocery_paths path)
{
	if (!ft_strcmp(path_loaded, path.path_shelf))
		return (TRUE);
	else if (!ft_strcmp(path_loaded, path.path_sprite))
		return (TRUE);
	else
		return (FALSE);
}

void		set_texture_type(t_doom *doom, const char *name,
				SDL_Surface *surface)
{
	uint8_t	i;

	i = 0;
	surface->userdata = ft_memalloc(sizeof(uint8_t));
	if (surface->userdata == NULL)
		doom_exit_failure(doom, "error: userdata malloc");
	ft_bzero(surface->userdata, sizeof(uint8_t));
	while (i < GROC_COUNT)
	{
		if (is_of_type(name, g_groc_paths[i]))
		{
			memcpy(surface->userdata, &g_groc_paths[i].type, sizeof(uint8_t));
			// printf("found type for %s  %d\n", name, g_groc_paths[i].type);	
			break ;
		}
		i++;
	}
	return ;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_library_struct.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:25 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/11 14:38:46 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			void_free_lib(void *lib)
{
	ft_bzero(lib, sizeof(lib));
	free(lib);
}

static void		free_sprites_textures(t_doom *doom, t_sprite *sprites)
{
	int i;
	int j;

	i = 0;
	while (i < doom->total_sprites)
	{
		ft_bzero(sprites[i].textures, sizeof(int*));
		free(sprites[i].textures);
		i++;
	}
}

void			free_struct_lib(t_doom *doom)
{
	if (doom->lib.sector)
		void_free_lib(doom->lib.sector);
	if (doom->lib.sidedef)
		void_free_lib(doom->lib.sidedef);
	if (doom->lib.sprites && doom->lib.sprites->textures)
		free_sprites_textures(doom, doom->lib.sprites);
	if (doom->lib.sprites)
		void_free_lib(doom->lib.sprites);
	if (doom->groceries)
		void_free_lib(doom->groceries);
	if (doom->hud)
		void_free_lib(doom->hud);
	if (doom->menu)
		void_free_lib(doom->menu);
}

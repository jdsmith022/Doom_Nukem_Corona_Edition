/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_utilities.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 17:00:42 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void		rmove(t_sprite *sprite, t_doom *doom)
{
	int i;

	i = 0;
	while (i < doom->total_sprites)
	{
		free(sprite[i].lines);
		free(sprite[i].textures);
		i++;
	}
	free(sprite);
}

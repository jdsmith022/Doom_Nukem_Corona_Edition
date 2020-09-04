/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_reset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:03 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/04 12:48:32 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		sprite_reset(t_doom *doom)
{
	int			i;
	t_sector	*sector;

	i = 0;
	sector = doom->lib.sector;
	while (i < doom->total_sprites)
	{
		doom->lib.sprites[i].visible = -1;
		doom->lib.sprites[i].n_sector = 0;
		i++;
	}
	i = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_reset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:03 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/02 16:17:14 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		sprite_reset(t_doom *doom)
{
	int		i;

	i = 0;
	while (i < doom->total_sprites)
	{
		doom->lib.sprites[i].visible = -1;
		doom->lib.sprites[i].n_sector = 0;
		i++;
	}
	i = 0;
	while (i < doom->lib.n_sectors)
	{
		doom->lib.sector[i].bottom.start.x = -1;
		doom->lib.sector[i].bottom.start.y = -1;
		doom->lib.sector[i].bottom.end.x = -1;
		doom->lib.sector[i].bottom.end.y = -1;
		doom->lib.sector[i].top.start.x = -1;
		doom->lib.sector[i].top.start.y = -1;
		doom->lib.sector[i].top.end.x = -1;
		doom->lib.sector[i].top.end.y = -1;
		doom->lib.sector[i].mid_bottom.start.x = -1;
		doom->lib.sector[i].mid_bottom.start.y = -1;
		doom->lib.sector[i].mid_bottom.end.x = -1;
		doom->lib.sector[i].mid_bottom.end.y = -1;
		doom->lib.sector[i].mid_top.start.x = -1;
		doom->lib.sector[i].mid_top.start.y = -1;
		doom->lib.sector[i].mid_top.end.x = -1;
		doom->lib.sector[i].mid_top.end.y = -1;
		i++;
	}
}

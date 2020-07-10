/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_reset.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:43:10 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/09 15:47:02 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		sprite_reset(t_doom *doom)
{
	int		i;

	i = 0;
	while (i < doom->total_sprites)
	{
		doom->lib.sprites[i].visible = -1;
		i++;
	}
}
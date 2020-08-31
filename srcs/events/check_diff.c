/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_diff.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:44:36 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/events.h"

int		check_sector_height_diff(t_doom *doom, int sector, int next_sector)
{
	bool	enough_height;

	enough_height = TRUE;
	doom->own_event.next_sector_height = \
	doom->cast.texture_height - \
	(doom->own_event.floor_diff + doom->own_event.ceiling_diff);
	if (doom->own_event.bend == FALSE && \
	doom->own_event.next_sector_height < PLAYER_HEIGHT)
		enough_height = FALSE;
	else if (doom->own_event.bend == TRUE && \
		doom->own_event.next_sector_height < doom->player.height)
		enough_height = FALSE;
	if (doom->player.height > doom->own_event.next_sector_height)
		enough_height = FALSE;
	return (enough_height);
}

int		check_floor_diff(t_doom *doom, int sector, int next_sector)
{
	int		floor_height;
	int		ceiling_height;
	int		next_floor_height;
	int		next_ceiling_height;
	int		too_high;

	too_high = FALSE;
	floor_height = doom->lib.sector[sector].height_floor;
	next_floor_height = doom->lib.sector[next_sector].height_floor;
	ceiling_height = doom->lib.sector[sector].height_ceiling;
	next_ceiling_height = doom->lib.sector[next_sector].height_floor;
	doom->own_event.floor_diff = next_floor_height - floor_height;
	doom->own_event.ceiling_diff = next_ceiling_height - ceiling_height;
	if (doom->own_event.floor_diff < 0)
		doom->own_event.step_down = TRUE;
	else if (doom->own_event.floor_diff > 0 && doom->own_event.jump == FALSE)
		too_high = TRUE;
	return (too_high);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move_position2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/26 18:18:41 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/07 18:16:45 by Malou         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	step_down(t_doom *doom, double dt)
{
	static double	duration = 1;
	int				height_floor;

	duration += dt;
	height_floor = doom->sector[doom->i_sector].height_floor;
	doom->player_height += GRAVITY * duration;
	if (doom->player_height <= PLAYER_HEIGHT + height_floor)
	{
		doom->player_height = PLAYER_HEIGHT + height_floor;
		doom->own_event.step_down = FALSE;
	}
}

void	jump_player(t_doom *doom, double dt)
{
	static double	duration = 1;
	double			og_height;
	int				jumpheight;

	doom->own_event.jump = 1;
	duration += dt;
	og_height = PLAYER_HEIGHT + doom->sector[doom->i_sector].height_floor;
	jumpheight = (int)(doom->own_event.velocity * duration);
	doom->player_height += jumpheight;
	doom->own_event.velocity += GRAVITY * duration;
	if (doom->player_height <= og_height + doom->own_event.floor_diff && jumpheight < 0)
	{
		doom->own_event.velocity = VELOCITY;
		doom->player_height = og_height + doom->own_event.floor_diff;
		doom->own_event.jump = 0;
		duration = 1;
	}
}

int		check_floor_diff(t_doom *doom, int sector, int next_sector)
{
	int		floor_height;
	int		next_floor_height;
	int		too_high;

	too_high = FALSE;
	floor_height = doom->sector[sector].height_floor;
	next_floor_height = doom->sector[next_sector].height_floor;
	doom->own_event.floor_diff = next_floor_height - floor_height;
	if (doom->own_event.floor_diff < 0)
		doom->own_event.step_down = TRUE;
	if (doom->own_event.floor_diff > 0 && doom->own_event.jump == 0)
		too_high = TRUE;
	return (too_high);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_action.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:18:04 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:31:57 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"

void	bend_down(t_doom *doom)
{
	int		og_height;
	int		height_floor;

	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	og_height = PLAYER_HEIGHT + height_floor;
	if (doom->player.height >= 40 && doom->own_event.bend == TRUE)
	{
		doom->player.height -= 20;
		if (doom->player.height < height_floor)
			doom->player.height = height_floor + 10;
	}
	else if (doom->player.height < \
	og_height && doom->own_event.bend == FALSE)
		doom->player.height += 20;
}

void	step_down(t_doom *doom, double dt)
{
	static double	duration = -0.1;
	int				height_floor;
	int				step;
	double			hold_height;

	duration += dt;
	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	step = (int)(GRAVITY * duration);
	doom->player.height += step;
	if (doom->player.height <= (PLAYER_HEIGHT + height_floor))
	{
		doom->player.height = PLAYER_HEIGHT + height_floor;
		doom->own_event.step_down = FALSE;
	}
}

void	jump_player(t_doom *doom, double dt)
{
	static double	duration = 0.5;
	double			og_height;
	int				height_floor;
	int				height_ceiling;
	int				jump_height;

	doom->own_event.jump = TRUE;
	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	height_ceiling = doom->lib.sector[doom->i_sector].height_ceiling;
	duration += dt;
	og_height = PLAYER_HEIGHT + height_floor;
	jump_height = (int)(doom->own_event.velocity * duration);
	if (((doom->player.height + jump_height) <= (doom->cast.texture_height - \
	(height_ceiling + height_floor)) && \
	((doom->player.height + jump_height) >= height_floor)))
		doom->player.height += jump_height;
	doom->own_event.velocity += GRAVITY * duration;
	if (doom->player.height <= og_height)
	{
		doom->own_event.velocity = VELOCITY;
		doom->player.height = og_height;
		doom->own_event.jump = FALSE;
		duration = 0.5;
	}
}

void	get_up(t_doom *doom, double dt)
{
	int				height_floor;
	int				height_ceiling;
	static double	duration = 0.1;
	int				jump_height;

	jump_height = \
		(int)(doom->own_event.velocity * duration) + (PLAYER_HEIGHT - 20);
	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	height_ceiling = doom->lib.sector[doom->i_sector].height_ceiling;
	if (((doom->player.height + jump_height) <= (doom->cast.texture_height - \
	(height_ceiling + height_floor)) && \
	((doom->player.height + jump_height) >= height_floor)))
		doom->player.height += jump_height;
	doom->own_event.fall = FALSE;
	doom->own_event.y_pitch = 0;
	doom->own_event.fall_count = 0;
}

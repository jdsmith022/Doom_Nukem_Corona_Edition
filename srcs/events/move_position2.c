#include "../../includes/doom.h"

void	bend_down(t_doom *doom)
{
	int		og_height;

	og_height = 100 + doom->lib.sector[doom->i_sector].height_floor;
	if (doom->player_height >= 0 && doom->own_event.bend == TRUE)
		doom->player_height -= 20;
	else if (doom->player_height < og_height && doom->own_event.bend == FALSE)
		doom->player_height += 20;
}

void	step_down(t_doom *doom, double dt)
{
	static double	duration = -1;
	int				height_floor;
	int				step;
	double			hold_height;

	duration += dt;
	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	step = (int)(GRAVITY * duration);
	doom->player_height += step;
 	if (doom->player_height <= (PLAYER_HEIGHT + height_floor))
	{
		doom->player_height = PLAYER_HEIGHT + height_floor;
		doom->own_event.step_down = FALSE;
	}
}

void	jump_player_2(t_doom *doom, double dt, \
			int jumpheight)
{
	static double	duration = 0.5;
	double			og_height;
	int				height_floor;
	int				prev_height;

	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	prev_height = doom->lib.sector[doom->prev_sector].height_floor;
	doom->own_event.jump = 1;
	duration += dt;
	og_height = PLAYER_HEIGHT + height_floor;
	jumpheight = (int)(doom->own_event.velocity * duration);
	if (prev_height > height_floor)
		jumpheight += prev_height - height_floor;
	doom->player_height += jumpheight;
	doom->own_event.velocity += GRAVITY * duration;
	if (doom->player_height <= og_height && \
		jumpheight < 0)
	{
		doom->own_event.velocity = VELOCITY;
		doom->player_height = og_height + doom->own_event.floor_diff;
		doom->own_event.jump = FALSE;
		duration = 0.5;
	}
}

void	jump_player(t_doom *doom, double dt)
{
	static double	duration = 0.1;
	int				jumpheight;

	if (doom->own_event.fall == TRUE)
	{
		jumpheight = (int)(doom->own_event.velocity * duration) + 298;
		doom->player_height += jumpheight;
		doom->own_event.fall = FALSE;
		return ;
	}
	jump_player_2(doom, dt, jumpheight);
}

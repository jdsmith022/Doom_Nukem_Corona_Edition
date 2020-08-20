#include "../../includes/doom.h"
#include "../../includes/action.h"

void	bend_down(t_doom *doom)
{
	int		og_height;

	og_height = PLAYER_HEIGHT + doom->lib.sector[doom->i_sector].height_floor;
	if (doom->player_height >= 20 && doom->own_event.bend == TRUE)
		doom->player_height -= 20;
	else if (doom->player_height < og_height && doom->own_event.bend == FALSE)
		doom->player_height += 20;
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
	int				height_ceiling;

	doom->own_event.jump = TRUE;
	height_floor = doom->lib.sector[doom->i_sector].height_floor;
	height_ceiling = doom->lib.sector[doom->i_sector].height_ceiling;
	duration += dt;
	og_height = PLAYER_HEIGHT + height_floor;
	jumpheight = (int)(doom->own_event.velocity * duration);
	doom->player_height += jumpheight;
	doom->own_event.velocity += GRAVITY * duration;
	if ((doom->player_height <= og_height  && \
	jumpheight <= 0) || (doom->player_height > \
	(doom->texture_height - (height_ceiling + height_floor))))
	{
		doom->own_event.velocity = VELOCITY;
		doom->player_height = og_height;
		doom->own_event.jump = FALSE;
		duration = 0.5;
	}
}

void	jump_player(t_doom *doom, double dt)
{
	t_sidedef		sidedef;
	static double	duration = 0.1;
	int				jumpheight;

	sidedef = doom->lib.sidedef[doom->i_sidedef];
	if (sidedef.action == 6)
		return ;
	if (doom->own_event.fall == TRUE)
	{
		jumpheight = \
			(int)(doom->own_event.velocity * duration) + (PLAYER_HEIGHT - 20);
		doom->player_height += jumpheight;
		doom->own_event.fall = FALSE;
		doom->own_event.y_pitch = 0;
		doom->own_event.fall_count = 0;
		return ;
	}
	jump_player_2(doom, dt, jumpheight);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mouse_events.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Malou <Malou@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/31 17:56:09 by Malou         #+#    #+#                 */
/*   Updated: 2020/06/23 15:51:31 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../game_editor/game_editor.h"

#include <stdio.h>

void	move_cam_direction(t_doom *doom, SDL_MouseMotionEvent *motion,\
	double dt)
{
	double	radian;
	int		dir_x;
	int		dir_y;

	radian = PI / 180;
	dir_x = 1;
	dir_y = 1;
	// printf("%d\n", motion->xrel);
	if (motion->xrel < 0)
		dir_x = -1;
	if (motion->yrel < 0)
		dir_y = -1;
	if (motion->yrel < 1)
		doom->dir_angle += CAM_SPEED * dir_x * dt;
	//doom->own_event.y_pitch += CAM_SPEED * dir_y * dt;
	if (doom->dir_angle < 0)
		doom->dir_angle += 360 * radian;
	if (doom->dir_angle > 360 * radian)
		doom->dir_angle -= 360 * radian;
	doom->own_event.hold_x = motion->x;
	doom->own_event.hold_y = motion->y;
}

void	mouse_release(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
		doom->own_event.mouse_press = 0;
}

void	game_editor_clicks(t_doom *doom, int x, int y)
{
	if (doom->game_design.portal_sec != -1 && 
	((x < AR_LEFT_SC_X || (x > AR_LEFT_SC_X + FRAME_WIDTH && x < AR_RIGHT_SC_X) || x > AR_RIGHT_SC_X + FRAME_WIDTH)
	|| (y < AR_LEFT_SC_Y || y > AR_LEFT_SC_Y + FRAME_HEIGHT)))
	{
		doom->game_design.portal_sec = -1;
		doom->game_design.portal_sd = -1;

	}
	if (x > MINUS_X && x < MINUS_X + FRAME_WIDTH && y > MINUS_Y && y < MINUS_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.s_len > 0)
			del_sector(doom);
	}
	else if (x > PLUS_X && x < PLUS_X + FRAME_WIDTH && y > PLUS_Y && y < PLUS_Y + FRAME_HEIGHT)
			add_sector(doom);
	else if (x > AR_RIGHT_M_X && x < AR_RIGHT_M_X + FRAME_WIDTH && y > AR_RIGHT_M_Y && y < AR_RIGHT_M_Y + FRAME_HEIGHT)
	{
		printf("fuck\n");
		doom->game_design.sector[doom->game_design.cur_sec].diff_x -= 10;
	}
	else if (x > AR_LEFT_M_X && x < AR_LEFT_M_X + FRAME_WIDTH && y > AR_LEFT_M_Y && y < AR_LEFT_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_x += 10;
	else if (x > AR_DOWN_M_X && x < AR_DOWN_M_X + FRAME_WIDTH && y > AR_DOWN_M_Y && y < AR_DOWN_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y += 10;
	else if (x > AR_UP_M_X && x < AR_UP_M_X + FRAME_WIDTH && y > AR_UP_M_Y && y < AR_UP_M_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].diff_y -= 10;
	else if (x > D_45_X && x < D_45_X + FRAME_WIDTH && y > D_45_Y && y < D_45_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = 45;
	else if (x > D_M45_X && x < D_M45_X + FRAME_WIDTH && y > D_M45_Y && y < D_M45_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = -45;
	else if (x > STRAIGHT_X && x < STRAIGHT_X + FRAME_WIDTH && y > STRAIGHT_Y && y < STRAIGHT_Y + FRAME_HEIGHT)
		doom->game_design.sector[doom->game_design.cur_sec].slope_floor = 0;
	else if (x > AR_LEFT_X && x < AR_LEFT_X + FRAME_WIDTH && y > AR_LEFT_Y && y < AR_LEFT_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sec > 0)
		{
			doom->game_design.cur_sec--;
			doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_RIGHT_X && x < AR_RIGHT_X + FRAME_WIDTH && y > AR_RIGHT_Y && y < AR_RIGHT_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sec < doom->game_design.s_len)
		{
			doom->game_design.cur_sec++;
			doom->game_design.cur_sd = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1;
		}
	}
	else if (x > AR_LEFT_S_X && x < AR_LEFT_S_X + FRAME_WIDTH && y > AR_LEFT_S_Y && y < AR_LEFT_S_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd > doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs - 1)
			doom->game_design.cur_sd--;
	}
	else if (x > AR_RIGHT_S_X && x < AR_RIGHT_S_X + FRAME_WIDTH && y > AR_RIGHT_S_Y && y < AR_RIGHT_S_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd <  doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs + doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
			doom->game_design.cur_sd++;	
	}
	else if (x > BAR_X && x < BAR_X + BAR_LEN && y > BAR_Y && y < BAR_Y + BAR_HEIGHT)
	{
		doom->game_design.sector[doom->game_design.cur_sec].height_floor = (float)(x - BAR_X) / BAR_LEN * BAR_DIFF + BAR_MIN;
	}
	else if (x > CROSS_X && x < CROSS_X + FRAME_WIDTH && y > CROSS_Y && y < CROSS_Y + FRAME_HEIGHT)
	{
		if (doom->game_design.cur_sd >= doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs)
			del_sidedef(doom);
	}
	else if (x > CROSS_P_X && x < CROSS_P_X + FRAME_WIDTH && y > CROSS_P_Y && y < CROSS_P_Y + FRAME_HEIGHT)
		doom->game_design.pl_pos = doom->game_design.pl_pos == 0 ? 1 : 0;
	else if (x > PORTAL_X && x < PORTAL_X + FRAME_WIDTH && y > PORTAL_Y && y < PORTAL_Y + FRAME_HEIGHT)
		add_portal(doom, 0);
	else if (x > WALL_X && x < WALL_X + FRAME_WIDTH && y > WALL_X && y < WALL_X + FRAME_HEIGHT)
		doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef = -1;
	else if (doom->game_design.portal_sec != -1 && x > AR_LEFT_SC_X && x < AR_LEFT_SC_X + FRAME_WIDTH && y > AR_LEFT_SC_Y && y < AR_LEFT_SC_Y + FRAME_HEIGHT)
		add_portal(doom, -1);
	else if (doom->game_design.portal_sec != -1 &&x > AR_RIGHT_SC_X && x < AR_RIGHT_SC_X + FRAME_WIDTH && y > AR_RIGHT_SC_Y && y < AR_RIGHT_SC_Y + FRAME_HEIGHT)	
		add_portal(doom, 1);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && doom->game_design.pl_pos == 0)
		add_sidedef(doom, x, y);
	else if (x > SIDEBAR_SECTOR && x < SIDEBAR_SIDEDEF && doom->game_design.pl_pos == 1)
	{
		doom->game_design.pl_x = x;
		doom->game_design.pl_y = y;
	}
}

void	mouse_press(t_doom *doom, SDL_MouseButtonEvent *button)
{
	if (button->button == SDL_BUTTON_LEFT)
	{
		doom->own_event.hold_x = button->x;
		doom->own_event.mouse_press = 1;
	}
	if (doom->game_editor == TRUE)
		game_editor_clicks(doom, button->x, button->y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_vanishing_box_coordinates.c                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:11:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 19:27:17 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			set_background_coords_middle_large(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = WIDTH / 2 - 320;
	doom->lib.font_lib.limit_x.y = WIDTH / 2 + 320;
	doom->lib.font_lib.limit_y.x = HEIGHT / 2 - 190;
	doom->lib.font_lib.limit_y.y = HEIGHT / 2 + 190;
}

void			set_background_coords_middle_narrow(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = WIDTH / 2 - 160;
	doom->lib.font_lib.limit_x.y = WIDTH / 2 + 160;
	doom->lib.font_lib.limit_y.x = HEIGHT / 2 + 150;
	doom->lib.font_lib.limit_y.y = HEIGHT / 2 + 200;
}

void			set_background_coords_middle_small(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = WIDTH / 2 - 310;
	doom->lib.font_lib.limit_x.y = WIDTH / 2 + 310;
	doom->lib.font_lib.limit_y.x = HEIGHT / 2 - 50;
	doom->lib.font_lib.limit_y.y = HEIGHT / 2 + 50;
}

void			set_background_coords_top(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = 25;
	doom->lib.font_lib.limit_x.y = 550;
	doom->lib.font_lib.limit_y.x = 50;
	doom->lib.font_lib.limit_y.y = 200;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_light_to_pixel.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:00:59 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 13:07:27 by nde-wild      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void	add_light_to_pixel_2(t_doom *doom, t_sector sector, int x, int y)
{
	double dist;

	dist = doom->cast.horizontal_plane_dist;
	doom->cast.distance = dist;
	doom->cast.distance = 1.0 / ((float)doom->cast.distance / 70.0);
	if (x > (WIDTH) / 2)
		doom->cast.distance -= \
			((float)x - (float)WIDTH / 2.0) * 1.0 / (float)WIDTH / 1.0;
	else
		doom->cast.distance = \
		+ doom->cast.distance - \
		((float)WIDTH / 2.0 - (float)x) * 1.0 / (float)WIDTH / 1.0;
	if (y > HEIGHT / 2)
		doom->cast.distance -= \
		((float)y - (float)HEIGHT / 2.0) * 1.0 / (float)HEIGHT;
	else
		doom->cast.distance = \
		+ doom->cast.distance - \
		((float)HEIGHT / 2.0 - (float)y) * 1.0 / (float)HEIGHT;
}

void		add_light_to_pixel(t_doom *doom, t_sector sector, int x, int y)
{
	double dist;

	dist = doom->cast.horizontal_plane_dist;
	if (doom->game.light == TRUE || sector.action == OUTSIDE)
	{
		if (sector.light == TRUE)
			doom->cast.distance = sector.light_level;
		else
			doom->cast.distance = 0.15;
	}
	else
		add_light_to_pixel_2(doom, sector, x, y);
}

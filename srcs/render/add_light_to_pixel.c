/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   add_light_to_pixel.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:00:59 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 14:00:59 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"


void	add_light_to_pixel(t_doom *doom, t_sector sector, int x, int y)
{
	double dist;

	dist = doom->horizontal_plane_dist;
	if (doom->light == TRUE)
	{
		if (sector.light == TRUE)
			doom->distance = sector.light_level;
		else
			doom->distance = 0.15;
	}
	else
	{
		doom->distance = dist;
		doom->distance = 1 / ((float)doom->distance / 70.0);
		if (x > WIDTH / 2)
			doom->distance -= (x - (float)WIDTH / 2.0) * 1.0 / (float)WIDTH;
		else
			doom->distance = \
			+doom->distance - ((float)WIDTH / 2.0 - x) * 1.0 / (float)WIDTH;
		if (y > HEIGHT / 2)
			doom->distance -= (y - (float)HEIGHT / 2.0) * 1.0 / (float)HEIGHT;
		else
			doom->distance = \
			+doom->distance - ((float)HEIGHT / 2.0 - y) * 1.0 / (float)HEIGHT;
	}
}

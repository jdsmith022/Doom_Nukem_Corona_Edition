/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture_properties.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 20:40:47 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/09 11:51:56 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void    set_texture_properties(t_doom *doom, t_sector sector, int texture)
{
    // if (sector.outside == TRUE)
	// {
	// 	doom->texture_width = 130;
	// 	doom->texture_height = 130;
	// 	doom->wall_height_std = 130;
	// }
	// else
	// {
		doom->texture_width = 64;
		doom->texture_height = 64;
		doom->wall_height_std = 64;
	// }
}

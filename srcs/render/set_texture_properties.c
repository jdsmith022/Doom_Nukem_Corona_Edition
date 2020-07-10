/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture_properties.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 20:40:47 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/10 11:04:43 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void    set_texture_properties(t_doom *doom, t_sector sector, int texture, int d)
{
	if (d == 0)
	{
		doom->texture_width = 64;
		doom->texture_height = 96;
		doom->vertical_height_std = doom->texture_height;
	}
	else
	{
		doom->texture_width = 64;
		doom->texture_height = 64;
		doom->horizontal_height_std = 64;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture_properties.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 20:40:47 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/07 15:25:58 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void    set_texture_properties(t_doom *doom, t_sector sector, int texture)
{
    if (sector.outside == TRUE)
	{
		doom->texture_width = 130;
		doom->texture_height = 130;
		doom->wall_height_std = 130;
	}
	else
	{
		doom->texture_width = doom->lib.tex_lib[texture]->w;
		doom->texture_height = doom->lib.tex_lib[texture]->h;
		doom->wall_height_std = doom->texture_height;
	}
}

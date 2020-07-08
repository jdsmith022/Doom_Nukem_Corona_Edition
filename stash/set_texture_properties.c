/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   set_texture_properties.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 20:40:47 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/07 10:41:28 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void    set_texture_properties(t_doom *doom, int sector, int id)
{
    if (doom->lib.sector[sector].outside == TRUE)
	{
		doom->texture_width = 128;
		doom->texture_height = 128;
		doom->wall_height_std = 128;
	}
	else
	{
		doom->texture_width = doom->lib.tex_lib[id]->w;
		doom->texture_height = doom->lib.tex_lib[id]->h;
	}
}

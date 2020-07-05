/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_skybox.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/05 11:14:16 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/05 13:29:54 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void	draw_skybox(t_doom *doom, int x, t_sidedef sidedef, t_plane plane)
{
	t_point	pixel;
	Uint32	tex_dex;
	Uint32	index;
	Uint32	wall_y;
	Uint32	pixel_dex;
	Uint8	bpp;

	pixel.y = plane.sidedef_top;
	pixel.x = x;
	tex_dex = doom->lib.sector[sidedef.sector].txt_ceiling;
	printf("tex: %d\n", tex_dex);
	}
}

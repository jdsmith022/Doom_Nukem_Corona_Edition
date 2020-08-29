/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_player_sprite.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:36 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 17:13:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/render.h"

void	print_player_sprite(t_doom *doom)
{
	SDL_Rect coord;

	coord.x = 250;
	coord.y = 5;
	draw_img(doom->lib.obj_lib[103], doom, coord);
	coord.x += 150;
	draw_img(doom->lib.obj_lib[105], doom, coord);
	coord.x += 150;
	draw_img(doom->lib.obj_lib[29], doom, coord);
}
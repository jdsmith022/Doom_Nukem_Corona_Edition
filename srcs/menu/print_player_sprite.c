/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_player_sprite.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:36 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/06 11:52:27 by jesmith       ########   odam.nl         */
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
	draw_img(doom->lib.player_lib[1], doom, coord);
	coord.x += 150;
	draw_img(doom->lib.player_lib[2], doom, coord);
	coord.x += 150;
	draw_img(doom->lib.player_lib[0], doom, coord);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   doom_init_window.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:47:10 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:47:29 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void			init_window(t_doom *doom)
{
	doom->lib.window.x_start = -1;
	doom->lib.window.x_end = WIDTH + 1;
	ft_bzero(doom->lib.window.y_pixel_bottom, WIDTH);
	ft_bzero(doom->lib.window.y_pixel_top, WIDTH);
	ft_bzero(doom->lib.window.height_standard, WIDTH);
	ft_bzero(doom->lib.window.wall_offset, WIDTH);
	doom->own_event.window = FALSE;
}

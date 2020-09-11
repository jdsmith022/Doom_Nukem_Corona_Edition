/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_screen.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:06 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 16:40:21 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"

void		update_screen(t_doom *doom)
{
	font_timer(doom);
	update_hud(doom);
	menus(doom);
	doom->own_event.mouse_press = FALSE;
}

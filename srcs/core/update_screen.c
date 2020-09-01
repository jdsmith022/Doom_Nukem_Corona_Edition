/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_screen.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:06 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:45:07 by jesmith       ########   odam.nl         */
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
}

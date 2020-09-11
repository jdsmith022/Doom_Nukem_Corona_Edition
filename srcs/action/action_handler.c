/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   action_handler.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:05:59 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 13:34:35 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

void			action_handler(t_doom *doom)
{
	if (doom->own_event.sanitizer_refills > 3)
		sanitizer_pause(doom);
	if (doom->own_event.light_switch == TRUE)
	{
		if (doom->own_event.click_light == -1)
			change_sector_light(doom);
		light_timer(doom, &doom->own_event.sd_action);
	}
	if (doom->own_event.fall == TRUE)
		player_fall(doom);
	if (doom->own_event.virus_red_i != -1)
		remove_red_virus(doom);
	if (doom->own_event.sliding_door != -1)
		render_sliding_door(doom, \
			&doom->lib.sidedef[doom->own_event.sliding_door]);
}

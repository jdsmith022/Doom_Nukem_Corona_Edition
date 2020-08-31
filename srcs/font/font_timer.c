/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_timer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:10:18 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:32:08 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"
#include "../../includes/hud.h"

static void		font_timer_3(t_doom *doom, t_event *event)
{
	if (doom->lib.sector[doom->i_sector].action == START_SECTOR && \
	doom->game.start_timer == FALSE && doom->lib.font_lib.bools.trolly == FALSE)
	{
		set_background_coords_middle_large(doom);
		font_timer_box_long(doom, \
			&doom->lib.font_lib.bools.start_sector, 10, 20);
	}
}

static void		font_timer_2(t_doom *doom, t_event *event)
{
	if (event->spray_shopper == TRUE)
		shopper_hit_random_font(doom);
	else if (doom->lib.sector[doom->i_sector].action == CHECKOUT)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.checkout, 21, 22);
	else if (doom->lib.font_lib.bools.trolly == TRUE && \
	doom->lib.sector[doom->i_sector].action == START_SECTOR)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 20, 21);
	else if (doom->lib.font_lib.bools.health_pack == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 25, 26);
	else if (doom->lib.font_lib.bools.facemask == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 26, 27);
	else if (doom->own_event.sanitizer_refills > 3 && \
	doom->cast.poster == refill_station)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 27, 28);
	else
		font_timer_3(doom, event);
}

void			font_timer(t_doom *doom)
{
	t_event	*event;

	event = &doom->own_event;
	set_background_coords_middle_small(doom);
	if (doom->lib.font_lib.bools.walking_text == TRUE \
	&& doom->game.editor == FALSE && \
	doom->lib.sector[doom->i_sector].action == OUTSIDE)
		font_timer_box_start(doom, \
			&doom->lib.font_lib.bools.text);
	else if (event->parked_too_close == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 7, 8);
	else if (event->scissor_lift == TRUE && \
	doom->lib.font_lib.bools.scissor_lift == TRUE)
		font_timer_box_long(doom, \
			&doom->lib.font_lib.bools.text, 3, 7);
	else if (event->fall == TRUE && event->fall_count == -1)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 8, 10);
	else
	{
		set_background_coords_middle_narrow(doom);
		font_timer_2(doom, event);
	}
}

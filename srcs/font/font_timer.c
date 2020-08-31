/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_timer.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:10:18 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 10:01:33 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"
#include "../../includes/hud.h"

static void		font_timer_box_short(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 2)
			print_vanishing_text_box(doom, start_dex, end_dex);
	}
}

static void		font_timer_box_long(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 15)
			print_vanishing_text_box(doom, start_dex, end_dex);
	}
}

static void		font_timer_box_start(t_doom *doom, bool *flag)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 5)
			print_vanishing_text_box(doom, 0, 3);
		else
			doom->lib.font_lib.bools.walking_text = FALSE;
	}
}

static void		font_timer_2(t_doom *doom, t_event *event)
{
	set_background_coords_middle_narrow(doom);
	if (event->spray_shopper == TRUE)
		shopper_hit_random_font(doom);
	else if (doom->lib.sector[doom->i_sector].action == CHECKOUT)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.checkout, 21, 22);
	else if (doom->lib.font_lib.bools.trolly == TRUE && \
	doom->lib.sector[doom->i_sector].action == START_SECTOR)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 25, 26);
	else if (doom->lib.font_lib.bools.health_pack == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 26, 27);
	else if (doom->lib.font_lib.bools.facemask == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 25, 26);
	else if (doom->lib.sector[doom->i_sector].action == START_SECTOR && \
	doom->start_timer == FALSE && doom->lib.font_lib.bools.trolly == FALSE)
	{
		set_background_coords_middle_large(doom);
		font_timer_box_long(doom, \
			&doom->lib.font_lib.bools.start_sector, 10, 20);
	}
}

void			font_timer(t_doom *doom)
{
	t_event	*event;

	event = &doom->own_event;
	set_background_coords_middle_small(doom);
	if (doom->lib.font_lib.bools.walking_text == TRUE \
	&& doom->game_editor == FALSE && \
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
		font_timer_2(doom, event);
}

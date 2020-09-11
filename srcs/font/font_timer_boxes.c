/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   font_timer_boxes.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:21:17 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/02 12:36:58 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

void		font_timer_box_short(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 2)
			print_vanishing_text_box(doom, start_dex, end_dex);
		else
		{
			if (start_dex == 26)
				doom->lib.font_lib.bools.facemask = FALSE;
			else if (start_dex == 25)
				doom->lib.font_lib.bools.health_pack = FALSE;
		}
	}
}

void		font_timer_box_long(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 15)
			print_vanishing_text_box(doom, start_dex, end_dex);
	}
}

void		font_timer_box_start(t_doom *doom, bool *flag)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game.play_time, &doom->lib.font_lib.timer);
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

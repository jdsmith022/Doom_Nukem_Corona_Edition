/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sanitizer_refill.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 16:17:29 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/07 12:33:56 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

void	sanitizer_pause(t_doom *doom)
{
	int diff;

	if (doom->own_event.sd_action == refill)
	{
		clock_gettime(doom->game.play_time, &doom->own_event.refill_pause);
		doom->own_event.sd_action = set;
		doom->lib.font_lib.bools.text = TRUE;
	}
	else
	{
		diff = find_time_difference(doom, doom->own_event.refill_pause.tv_sec);
		if (diff > 10)
		{
			doom->own_event.refill = FALSE;
			doom->own_event.sanitizer_refills = 0;
		}
	}
}

static void	check_poster(t_doom *doom)
{
	if (doom->lib.sidedef[doom->i_sidedef].action == 8)
	{
		doom->own_event.refill = TRUE;
		doom->own_event.sd_action = refill;
	}
}

void		sanitizer_refill(t_doom *doom)
{
	if (doom->own_event.refill == FALSE)
		check_poster(doom);
	if (doom->own_event.refill == TRUE)
	{
		doom->own_event.sanitizer_refills += 1;
		if (doom->own_event.sanitizer_refills < 3 \
		&& doom->own_event.sanitizer_refills > 0)
			doom->hud->update = sanitizer;
	}
}

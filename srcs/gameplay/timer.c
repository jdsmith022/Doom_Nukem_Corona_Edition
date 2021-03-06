/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:44:35 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 17:29:07 by elkanfrank    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/menu.h"
#include "../../includes/audio.h"

static void	show_invisible_sprite(t_doom *doom)
{
	Uint32 index;

	index = 0;
	while (index < doom->total_sprites)
	{
		if (doom->lib.sprites[index].action == 8)
			doom->lib.sprites[index].action = 11;
		index++;
	}
}

void		timer(t_doom *doom)
{
	struct timespec	curr_time;
	int				diff;

	if (doom->lib.sector[doom->i_sector].action == START_TIMER && \
	doom->menu->start_timer == FALSE)
	{
		doom->game.start_timer = TRUE;
		doom->menu->start_timer = TRUE;
		show_invisible_sprite(doom);
		clock_gettime(doom->game.play_time, &doom->game.start_time);
	}
	else if (doom->menu->state != game_paused && doom->game.editor == FALSE \
	&& doom->menu->start_timer == TRUE)
	{
		doom->game.start_timer = FALSE;
		clock_gettime(doom->game.play_time, &curr_time);
		diff = curr_time.tv_sec - doom->game.start_time.tv_sec;
		doom->hud->curr_time = doom->hud->hold_time - diff;
		if (doom->hud->curr_time == 0)
			doom->menu->state = game_over;
	}
}

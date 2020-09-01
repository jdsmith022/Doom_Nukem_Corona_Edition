/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_difference.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:11:56 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/31 17:22:16 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

int				find_time_difference(t_doom *doom, time_t lib_timer)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	clock_gettime(doom->game.play_time, &time);
	sec = lib_timer;
	diff = time.tv_sec - sec;
	return (diff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   time_difference.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:17:08 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:17:09 by jessicasmit   ########   odam.nl         */
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

	clock_gettime(doom->game_time, &time);
	sec = lib_timer;
	diff = time.tv_sec - sec;
	return (diff);
}

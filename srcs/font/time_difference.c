
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

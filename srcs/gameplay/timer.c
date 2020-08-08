#include "../../includes/doom.h"
#include "../../includes/hud.h"

void		timer(t_doom *doom)
{
	time_t   sec;
	int		ret;

	if (doom->hud->start == TRUE)
	{
		ret = clock_gettime(doom->game_time, sec);
		if (ret == -1)
			doom_exit_failure(doom, "error: Timer failure.");
	}
}
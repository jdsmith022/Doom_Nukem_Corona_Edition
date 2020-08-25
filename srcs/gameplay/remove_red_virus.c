#include "../../includes/doom.h"
#include "../../includes/font.h"

/*
**		timer for letting red virus disappear after 5 seconds
**		eventually you could send a function as parameter
**		if you put this function in a different file take font.h with you
*/

void			remove_red_virus(t_doom *doom)
{
	int			diff;

	diff = 0;
	if (doom->own_event.virus_red == TRUE)
	{
		clock_gettime(doom->game_time, &doom->own_event.sprite_timer);
		doom->own_event.virus_red = FALSE;
	}
	else
	{
		diff = find_time_difference(doom, doom->own_event.sprite_timer.tv_sec);
		if (diff <= 3)
		{
			SPRITES[doom->own_event.virus_red_i].action = 6;
			doom->own_event.virus_red_i = -1;
		}
	}
}

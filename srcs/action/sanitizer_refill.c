#include "../../includes/doom.h"
#include "../../includes/action.h"
#include "../../includes/gameplay.h"
#include "../../includes/hud.h"

static void	sanitizer_pause(t_doom *doom)
{
	int diff;

	if (doom->own_event.action == TRUE)
	{
		clock_gettime(doom->game_time, &doom->own_event.refill_pause);
		doom->own_event.action = FALSE;
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
		doom->own_event.action = TRUE;
	}
}

void	sanitizer_refill(t_doom *doom)
{
	if (MOUSE_PRESSED && doom->own_event.refill == FALSE)
		check_poster(doom);
	if (MOUSE_PRESSED && doom->own_event.refill == TRUE)
	{
		doom->own_event.sanitizer_refills += 1;
		if (doom->own_event.sanitizer_refills < 3 \
		&& doom->own_event.sanitizer_refills > 0)
			doom->hud->sanitizer = TRUE;
		doom->own_event.mouse_press = FALSE;
	}
	if (doom->own_event.refill == TRUE && doom->own_event.mouse_press == FALSE)
	{
		if (doom->own_event.sanitizer_refills > 3)
			sanitizer_pause(doom);
	}
}

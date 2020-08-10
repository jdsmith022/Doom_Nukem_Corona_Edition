#include "../../includes/doom.h"
#include "../../includes/font.h"

static int			find_time_difference(t_doom *doom)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	clock_gettime(doom->game_time, &time);
	sec = doom->lib.font_lib.timer.tv_sec;
	diff = time.tv_sec - sec;
	return (diff);
}

static void		font_timer_scissor_lift(t_doom *doom, bool scissor_flag,
					int start_dex, int end_dex)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	// if (doom->proximity == TRUE)
	// 	set_background_coords_middle(doom);
	if (scissor_flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		scissor_flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom);
		if (diff <= 20)
			print_vanishing_text_box(doom, start_dex, end_dex);
	}
}


void				font_timer(t_doom *doom)
{
	int				diff;

	set_background_coords_top(doom);
	if (doom->lib.font_lib.bools.walking_info == TRUE \
	&& doom->game_editor == FALSE)
	{
		diff = find_time_difference(doom);
		if (diff <= 10)
			print_vanishing_text_box(doom, 0, 3);
		else
			doom->lib.font_lib.bools.walking_info = FALSE;
	}
	if (doom->lib.font_lib.bools.shooting_info == TRUE)
	{
		diff = find_time_difference(doom);
		if (diff <= 10)
			print_vanishing_text_box(doom, 3, 5);
		else
			doom->lib.font_lib.bools.shooting_info = FALSE;
	}
	else if (doom->save_scissor_lift == TRUE)
		font_timer_scissor_lift(doom, \
			doom->lib.font_lib.bools.scissor_lift, 3, 7);
	// else if (doom->scissor_lift_prox == TRUE)
		// font_timer_scissor_lift(doom, \
				doom->lib.font_lib.bools.scissor_lift, 7, 8);
}

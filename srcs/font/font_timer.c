#include "../../includes/doom.h"
#include "../../includes/font.h"

static void		font_timer_box_short(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom);
		if (diff <= 3)
		{
			print_vanishing_text_box(doom, start_dex, end_dex);
		}
	}
}

static void		font_timer_box_long(t_doom *doom, bool *flag,
					int start_dex, int end_dex)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom);
		if (diff <= 10)
			print_vanishing_text_box(doom, start_dex, end_dex);
	}
}

static void		font_timer_box_start(t_doom *doom, bool *flag)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			sec;

	if (*flag == TRUE)
	{
		clock_gettime(doom->game_time, &doom->lib.font_lib.timer);
		*flag = FALSE;
	}
	else
	{
		diff = find_time_difference(doom);
		if (diff <= 8)
			print_vanishing_text_box(doom, 0, 3);
		else
			doom->lib.font_lib.bools.walking_text = FALSE;
	}
}

static void			font_timer_2(t_doom *doom)
{
	if (doom->lib.sector[doom->i_sector].action == CHECKOUT)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.checkout, 17, 18);
	else if (doom->lib.sector[doom->i_sector].action == START_SECTOR)
	{
		set_background_coords_middle_large(doom);
		font_timer_box_long(doom, \
			&doom->lib.font_lib.bools.start_sector, 10, 16);
	}
	// else if (doom->lib.sector[doom->i_sector].action == TROLLY && doom->own_event.trolly == FALSE)
	// {
	// 	set_background_coords_middle_small(doom);
	// 	font_timer_box_long(doom, \
	// 		&doom->lib.font_lib.bools.start_sector, 16, 17);
	// }
}

void				font_timer(t_doom *doom)
{
	set_background_coords_middle_small(doom);
	if (doom->own_event.parked_too_close == TRUE)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 7, 8);
	else if (doom->save_scissor_lift == TRUE)
		font_timer_box_long(doom, \
			&doom->lib.font_lib.bools.text, 3, 7);
	else if (doom->own_event.fall == TRUE && \
	doom->own_event.fall_count != -1)
		font_timer_box_short(doom, \
			&doom->lib.font_lib.bools.text, 8, 10);
	else if (doom->lib.font_lib.bools.walking_text == TRUE \
	&& doom->game_editor == FALSE)
		font_timer_box_start(doom, \
			&doom->lib.font_lib.bools.text);
	else
		font_timer_2(doom);
}

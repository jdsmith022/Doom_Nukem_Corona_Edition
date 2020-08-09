#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	draw_font_instructions(t_doom *doom, t_font *font_lib,
				int start_dex, int end_dex)
{
	int		ret;

	start_dex = 0;
	while (start_dex < end_dex)
	{
		ret = SDL_BlitSurface(font_lib[start_dex].font_surface, NULL,\
			doom->surface, &font_lib[start_dex].font_rect);
		if (ret == -1)
			doom_exit_failure(doom, FONT_ERR);
		start_dex++;
	}
}

void		font_timer(t_doom *doom)
{
	int				diff;
	clockid_t		clkid;
	struct timespec	time;
	time_t			set;

	if (doom->lib.font_lib.walking_info == TRUE && doom->game_editor == FALSE)
	{
		clock_gettime(doom->game_time, &time);
		set = doom->lib.font_lib.timer.tv_sec;
		diff = time.tv_sec - set;
		if (diff <= 10)
			draw_font_instructions(doom, doom->lib.font_lib.instruction_font,\
				0, 3);
		else
			doom->lib.font_lib.walking_info = FALSE;
	}
	if (doom->lib.font_lib.shooting_info == TRUE)
	{
		clock_gettime(doom->game_time, &time);
		set = doom->lib.font_lib.timer.tv_sec;
		diff = time.tv_sec - set;
		if (diff <= 10)
			draw_font_instructions(doom, doom->lib.font_lib.instruction_font,\
				3, 5);
		else
			doom->lib.font_lib.shooting_info = FALSE;
	}
}

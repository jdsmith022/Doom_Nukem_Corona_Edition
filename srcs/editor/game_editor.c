#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

#include <stdio.h>

void	open_game_editor(t_doom *doom)
{
	Uint32				*pixels;
	int					i;
	struct timespec		hold_time;
	struct timespec		curr_time;

	clock_gettime(doom->game.play_time, &hold_time);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->cast.distance = 1;
	pixels = doom->surface->pixels;
	if (doom->game_design.sector == NULL)
		init_game_design(doom);
	draw_screen_colors(pixels, doom);
	draw_images(pixels, doom);
	bars(&pixels, doom);
	i = doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs;
	while (i < doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs\
		+ doom->game_design.sector[doom->game_design.cur_sec].n_sidedefs)
	{
		draw_lines(doom, &pixels, i);
		i++;
	}
	draw_object(doom, &pixels);
	clock_gettime(doom->game.play_time, &curr_time);
	doom->game.start_time.tv_sec = doom->game.start_time.tv_sec +\
		(curr_time.tv_sec - hold_time.tv_sec);
}

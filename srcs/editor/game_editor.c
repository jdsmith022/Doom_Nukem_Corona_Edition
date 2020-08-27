#include "../../includes/doom.h"
#include "game_editor.h"

#include <stdio.h>

void	open_game_editor(t_doom *doom)
{
	Uint32				*pixels;
	int					i;
	struct timespec		hold_time;
	struct timespec		curr_time;

	// hold_time = SDL_GetTicks();
	clock_gettime(doom->game_time, &hold_time);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	doom->distance = 1;
	pixels = doom->surface->pixels;
	if (SECTOR == NULL)
		init_game_design(doom);
	draw_screen_colors(pixels, doom);
	draw_images(pixels, doom);
	bars(&pixels, doom);
	i = SECTOR[EDIT.cur_sec].i_sidedefs;
	while (i < SECTOR[EDIT.cur_sec].i_sidedefs\
		+ SECTOR[EDIT.cur_sec].n_sidedefs)
	{
		draw_lines(doom, &pixels, i);
		i++;
	}
	draw_object(doom, &pixels);
	// curr_time = SDL_GetTicks();
	clock_gettime(doom->game_time, &curr_time);
	doom->game_start_time.tv_sec = doom->game_start_time.tv_sec + (curr_time.tv_sec - hold_time.tv_sec);
}

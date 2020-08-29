#include "../../includes/doom.h"
#include "../../includes/font.h"
#include "../../includes/sprites.h"

int				virus_move(int bottom, int height, int val,\
				int sprite_index)
{
	int		move;

	move = (height * 2) / 8;
	if (sprite_index % 5 == 0)
	{
		if (val == 0 || val == 19)
			bottom = bottom - (4.5 * move);
		else if (val == 1 || val == 18)
			bottom = bottom - (4 * move);
		else if (val == 2 || val == 17)
			bottom = bottom - (3 * move);
		else if (val == 3 || val == 16)
			bottom = bottom - (2 * move);
		else if (val == 4 || val == 15)
			bottom = bottom - move;
		else if (val == 6 || val == 13)
			bottom = bottom + move;
		else if (val == 7 || val == 12)
			bottom = bottom + (2 * move);
		else if (val == 8 || val == 11)
			bottom = bottom + (3 * move);
		else if (val == 9 || val == 10)
			bottom = bottom + (4 * move);
	}
	else if (sprite_index %5 == 1)
	{
		if (val == 4 || val == 13 || val == 14 || val == 3)
			bottom = bottom - (2 * move);
		else if (val == 5 || val == 12 || val == 15 || val == 2)
			bottom = bottom - move;
		else if (val == 7 || val == 10 || val == 17 || val == 0)
			bottom = bottom + move;
		else if (val == 8 || val == 9 || val == 18 || val == 19)
			bottom = bottom + (2 * move);
	}
	else if (sprite_index % 5 == 2)
	{
		if (val == 0 || val == 9 || val == 10 || val == 19)
			bottom = bottom - (2 * move);
		else if (val == 1 || val == 8 || val == 11 || val == 18)
			bottom = bottom - move;
		else if (val == 3 || val == 6 || val == 13 || val == 16)
			bottom = bottom + move;
		else if (val == 4 || val == 5 || val == 14 || val == 15)
			bottom = bottom + (2 * move);
	}
	else if (sprite_index % 5 == 3)
	{
		if (val == 7 || val == 6)
			bottom = bottom - (4.5 * move);
		else if (val == 8 || val == 5)
			bottom = bottom - (4 * move);
		else if (val == 9 || val == 4)
			bottom = bottom - (3 * move);
		else if (val == 10 || val == 3)
			bottom = bottom - (2 * move);
		else if (val == 11 || val == 2)
			bottom = bottom - move;
		else if (val == 13 || val == 0)
			bottom = bottom + move;
		else if (val == 14 || val == 19)
			bottom = bottom + (2 * move);
		else if (val == 15 || val == 18)
			bottom = bottom + (3 * move);
		else if (val == 16 || val == 17)
			bottom = bottom + (4 * move);	
	}
	else
	{
		if (val == 7 || val == 6)
			bottom = bottom - (2 * move);
		else if (val == 8 || val == 5)
			bottom = bottom - move;
		else if (val == 10 || val == 13 || val == 15 || val == 15\
				|| val == 18 || val == 0 || val == 3)
			bottom = bottom + move;
		else if (val == 11 || val == 12 || val == 16 || val == 17\
				|| val == 1 || val == 2)
			bottom = bottom + (2 * move);
	}
	return (bottom);

}

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
			doom->lib.sprites[doom->own_event.virus_red_i].action = 6;
			doom->own_event.virus_red_i = -1;
		}
	}
}

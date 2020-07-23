#include "../../includes/doom.h"
#include "game_editor.h"


void    draw_bar_point(Uint32 **pixels, t_bar bar)
{
	double place;
	int i;
	int j;

	place = bar.cur_height;
	place -= bar.min;
	place /= bar.diff;
	place *= bar.len;
	place += bar.x;
	i = 0;
	j = 0;
	while (j < 9)
	{
		while (i < 8)
		{
			pixels[0][(((bar.y - 2 + j) * WIDTH) + (int)place - 4 + i)] = 0xff800000;
			i++;
		}
		i = 0;
		j++;
	}
}
void    draw_bar(Uint32 **pixels, t_bar bar)
{
	int i;
	int safe;

	i = 0;
	safe = bar.x;
	while ((double)i / bar.len != (double)bar.height)
	{
		pixels[0][((bar.y * WIDTH) + bar.x)] = 0xff333333;
		bar.x++;
		if (bar.x - bar.len == safe)
		{
			bar.x = safe;
			bar.y++;
		}
		i++;
	}
}

void    bars(Uint32 **pixels, t_doom *doom)
{
	t_bar bar;

	bar.min = HF_MIN;
	bar.max = HF_MAX;
	bar.diff = HF_DIFF;
	bar.x = HF_X;
	bar.y = HF_Y;
	bar.height = HF_HEIGHT;
	bar.len = HF_LEN;
	bar.cur_height = doom->game_design.sector[doom->game_design.cur_sec].height_floor;
	draw_bar(pixels, bar);
	draw_bar_point(pixels, bar);
	bar.min = HC_MIN;
	bar.max = HC_MAX;
	bar.diff = HC_DIFF;
	bar.x = HC_X;
	bar.y = HC_Y;
	bar.height = HC_HEIGHT;
	bar.len = HC_LEN;
	bar.cur_height = doom->game_design.sector[doom->game_design.cur_sec].height_ceiling;
	draw_bar(pixels, bar);
	draw_bar_point(pixels, bar);
	bar.min = LL_MIN;
	bar.max = LL_MAX;
	bar.diff = LL_DIFF;
	bar.x = LL_X;
	bar.y = LL_Y;
	bar.height = LL_HEIGHT;
	bar.len = LL_LEN;
	bar.cur_height = doom->game_design.sector[doom->game_design.cur_sec].light_level;
	draw_bar(pixels, bar);
	draw_bar_point(pixels, bar);
}
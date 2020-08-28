/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shopper_hit_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:11:46 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/28 20:07:54 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void		draw_random_font(t_doom *doom, t_font *font_lib, Uint32 index)
{
	int		ret;

	ret = SDL_BlitSurface(font_lib[index].font_surface, NULL,\
		doom->surface, &font_lib[index].font_rect);
	if (ret < 0)
		doom_exit_failure(doom, "error: Font to screen");
}

static void		print_random_font(t_doom *doom, bool *flag, Uint32 index)
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
		diff = find_time_difference(doom, doom->lib.font_lib.timer.tv_sec);
		if (diff <= 1)
			draw_random_font(doom, doom->lib.font_lib.instruction_font, index);
		else
			doom->own_event.spray_shopper = FALSE;
	}
}

static void		select_index(t_doom *doom)
{
	Uint32		random_dex;
	static int	shopper_array[3] = { 21, 22, 23 };

	random_dex = rand() % 3;
	random_dex = shopper_array[random_dex];
	doom->lib.font_lib.random_index = random_dex;
}

void			shopper_hit_random_font(t_doom *doom)
{
	if (doom->lib.font_lib.bools.text == TRUE)
		select_index(doom);
	print_instruction_background(doom, doom->lib.font_lib.limit_x, \
		doom->lib.font_lib.limit_y);
	print_random_font(doom, &doom->lib.font_lib.bools.text,\
		doom->lib.font_lib.random_index);
}

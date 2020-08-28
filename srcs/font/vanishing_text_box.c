/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vanishing_text_box.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 12:17:13 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/08/28 12:17:15 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void		draw_font_instructions(t_doom *doom, t_font *font_lib,
				int start_dex, int end_dex)
{
	while (start_dex < end_dex)
	{
		SDL_BlitSurface(font_lib[start_dex].font_surface, NULL,\
			doom->surface, &font_lib[start_dex].font_rect);
		start_dex++;
	}
}

void			print_instruction_background(t_doom *doom,
				t_limit limit_x, t_limit limit_y)
{
	Uint32	*pixels;
	Uint32	color;
	int		x;
	int		y;

	pixels = doom->surface->pixels;
	x = limit_x.x;
	while (x < limit_x.y)
	{
		y = limit_y.x;
		while (y < limit_y.y)
		{
			color = pixels[(y * WIDTH) + x];
			add_tint_to_color(&color, BLUE, FONT_MASK);
			if (x >= limit_x.x && x <= limit_x.y && \
			y >= limit_y.x && y <= limit_y.y)
				pixels[(y * WIDTH + x)] = color;
			y++;
		}
		x++;
	}
}

void			print_vanishing_text_box(t_doom *doom,
				int start, int stop)
{
	print_instruction_background(doom, doom->lib.font_lib.limit_x, \
		doom->lib.font_lib.limit_y);
	draw_font_instructions(doom, doom->lib.font_lib.instruction_font,\
		start, stop);
}

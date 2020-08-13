#include "../../includes/doom.h"
#include "../../includes/font.h"

static void		draw_font_instructions(t_doom *doom, t_font *font_lib,
				int start_dex, int end_dex)
{
	int ret;

	while (start_dex < end_dex)
	{
		ret = SDL_BlitSurface(font_lib[start_dex].font_surface, NULL,\
			doom->surface, &font_lib[start_dex].font_rect);
		if (ret < 0)
			doom_exit_failure(doom, "error: Font to screen");
		start_dex++;
	}
}

static void		print_instruction_background(t_doom *doom,
					t_limit limit_x, t_limit limit_y)
{
	Uint32	*pixels;
	int		x;
	int		y;

	pixels = doom->surface->pixels;
	x = limit_x.x;
	while (x < limit_x.y)
	{
		y = limit_y.x;
		while (y < limit_y.y)
		{
			if (x >= limit_x.x && x <= limit_x.y && \
			y >= limit_y.x && y <= limit_y.y)
				pixels[(y * WIDTH + x)] = 0xEFEFEF;
			y++;
		}
		x++;
	}
}

void		print_vanishing_text_box(t_doom *doom,
				int start, int stop)
{
	print_instruction_background(doom, doom->lib.font_lib.limit_x, \
		doom->lib.font_lib.limit_y);
	draw_font_instructions(doom, doom->lib.font_lib.instruction_font,\
		start, stop);
}
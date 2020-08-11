#include "../../includes/doom.h"
#include "../../includes/font.h"

void			set_background_coords_middle(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = WIDTH / 2 - 300;
	doom->lib.font_lib.limit_x.y = WIDTH / 2 + 300;
	doom->lib.font_lib.limit_y.x = HEIGHT / 2 - 50;
	doom->lib.font_lib.limit_y.y = HEIGHT / 2 + 50;
}

void			set_background_coords_top(t_doom *doom)
{
	doom->lib.font_lib.limit_x.x = 25;
	doom->lib.font_lib.limit_x.y = 550;
	doom->lib.font_lib.limit_y.x = 50;
	doom->lib.font_lib.limit_y.y = 200;
}

static void		draw_font_instructions(t_doom *doom, t_font *font_lib,
				int start_dex, int end_dex)
{
	int		ret;

	while (start_dex < end_dex)
	{
		ret = SDL_BlitSurface(font_lib[start_dex].font_surface, NULL,\
			doom->surface, &font_lib[start_dex].font_rect);
		if (ret == -1)
			doom_exit_failure(doom, FONT_ERR);
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
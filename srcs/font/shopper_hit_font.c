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

void		shopper_hit_font(t_doom *doom)
{
	Uint32		random_dex;
	static int	shopper_array[3] = { 18, 19, 20 };

	random_dex = rand() % 3;
	printf("random: %d\n", random_dex);
	set_background_coords_middle_small(doom);
	print_instruction_background(doom, doom->lib.font_lib.limit_x, \
		doom->lib.font_lib.limit_y);
	draw_random_font(doom, doom->lib.font_lib.instruction_font, random_dex);
}
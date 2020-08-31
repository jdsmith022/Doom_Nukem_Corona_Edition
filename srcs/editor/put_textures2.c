#include "../../includes/doom.h"
#include "game_editor.h"
#include "sprites.h"
#include "../../includes/render.h"

void		draw_screen_colors(Uint32 *pixels, t_doom *doom)
{
	int x;
	int y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (x < WIDTH - (WIDTH / 5) && x > WIDTH / 5)
				pixels[((y * WIDTH) + x)] = 0;
			else
				pixels[((y * WIDTH) + x)] = 0x8c3cde6;
			x++;
		}
		y++;
	}
}

void		put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
				Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;

	pixels = doom->surface->pixels;
	texture = doom->game_design.sym_lib[tex_dex]->pixels;
	pixels[index] = texture[pixel_dex];
	pixels[index + 1] = texture[pixel_dex + 1];
	pixels[index + 2] = texture[pixel_dex + 2];
}

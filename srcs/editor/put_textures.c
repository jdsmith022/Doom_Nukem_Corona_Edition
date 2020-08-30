#include "../../includes/doom.h"
#include "game_editor.h"
#include "sprites.h"

void    draw_screen_colors(Uint32 *pixels, t_doom *doom)
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

void put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
				Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;

	pixels = doom->surface->pixels;
	texture = doom->game_design.sym_lib[tex_dex]->pixels;
	pixels[index] =  texture[pixel_dex];
	pixels[index + 1] = texture[pixel_dex + 1];
	pixels[index + 2] = texture[pixel_dex + 2];
}

void    put_textures(int x, int y, int index, t_doom *doom)
{
    int				save_x;
	Uint32			shift;
	t_point			i;
	t_point			change;
	SDL_Surface		*texture;


    save_x = x;
    i.x = 0;
	i.y = 0;
	texture = doom->game_design.sidedef_bar == 1 ? \
	doom->lib.tex_lib[index] : doom->lib.obj_lib[index];
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
	change.x = (double)texture->w / 48.0;
	change.y = (double)texture->h / 48.0;
    while ((int)i.y < texture->h)
    {
		put_texture(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4),\
		(Uint32)(((int)i.y * texture->w + (int)i.x) * shift));
		x++;
		i.x += change.x;
        if ((int)i.x >= texture->w)
        {
            x = save_x;
            y++;
			i.x = 0;
			i.y += change.y;
        }
    }
}

void	put_images(int x, int y, int index, t_doom *doom)
{
    int     save_x;
	Uint32  shift;
	t_point i;
	t_point change;

    save_x = x;
    i.x = 0;
	i.y = 0;
	shift = doom->game_design.sym_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
	change.x = (double)doom->game_design.sym_lib[index]->w / 32.0;
	change.y = (double)doom->game_design.sym_lib[index]->h / 32.0;
    while ((int)i.y < doom->game_design.sym_lib[index]->h)
    {
		put_symbol(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4),\
		(Uint32)(((int)i.y * doom->game_design.sym_lib[index]->w + (int)i.x) * shift));
		x++;
		i.x += change.x;
        if ((int)i.x >= doom->game_design.sym_lib[index]->w)
        {
            x = save_x;
            y++;
			i.x = 0;
			i.y += change.y;
        }
    }
}

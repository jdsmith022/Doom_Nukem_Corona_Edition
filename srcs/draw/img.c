#include "../../includes/doom.h"

void		put_pixel(SDL_Surface *texture, t_doom *doom, Uint32 index, Uint32 pixel_dex)
{
	char	*pixels;
	char	R;
	char	G;
	char	B;
	
	pixels = doom->surface->pixels;
	R = (char)texture->pixels + pixel_dex;
	G = (char)texture->pixels + pixel_dex + 1;
	B = (char)texture->pixels + pixel_dex + 2;
	// R = 127;
	// G = 0;
	// B = 0;
	add_saturation(&R, &G, &B, doom->distance);
	pixels[index] = R;
	pixels[index + 1] = G;
	pixels[index + 2] = B;
}

void	draw_texture(SDL_Surface *texture, t_doom *doom, int x, int y)
{
	uint32_t	shift;
    int			save_x;
    int			sx;

    save_x = x;
    sx = 0;
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
    while (sx < (texture->h * texture->w))
    {
		put_pixel(texture, doom, (Uint32)((y * WIDTH + x) * 4), (Uint32)(sx * shift));
		x++;
		sx++;
        if (sx % (texture->w) == 0)
        {
            x = save_x;
            y++;
        }
    }
	return ;
}

#include "../../includes/doom.h"

void		put_pixel_from_img(SDL_Surface *texture, t_doom *doom, Uint32 index, Uint32 curr_pixel)
{
	char	*pixels;
	t_rgb	rgb;

	pixels = doom->surface->pixels;
	rgb.r = *((char *)texture->pixels + curr_pixel);
	rgb.g = *((char *)texture->pixels + curr_pixel + 1);
	rgb.b = *((char *)texture->pixels + curr_pixel + 2);
	add_saturation(&rgb.r, &rgb.g, &rgb.b, doom->distance);
	ft_memcpy(doom->surface->pixels + index, &rgb, sizeof(t_rgb));
}

void	draw_img(SDL_Surface *texture, t_doom *doom, int x, int y)
{
	Uint32	shift;
    int		save_x;
    int		sx;

    save_x = x;
    sx = 0;
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
    while (sx < (texture->h * texture->w))
    {
		put_pixel_from_img(texture, doom, (y * WIDTH + x) * 4, sx * shift);
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

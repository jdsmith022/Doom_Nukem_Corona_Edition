/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   img.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/29 14:02:27 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 18:37:41 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/render.h"

static void		put_pixel_from_img(char *img_pixels, t_doom *doom,
					uint32_t index)
{
	char		*pixels;
	t_rgb		color;

	pixels = doom->surface->pixels;
	color.r = *img_pixels;
	color.g = *(img_pixels + 1);
	color.b = *(img_pixels + 2);
	if (color.r == 255 && color.b == 255 && color.g == 255)
		return ;
	ft_memcpy(doom->surface->pixels + index, &color, sizeof(t_rgb));
}

void			draw_img(SDL_Surface *texture, t_doom *doom, SDL_Rect coord)
{
	uint32_t	shift;
	uint16_t	prev_x;
	uint16_t	sx;
	uint32_t	screen_index;

	if (!texture)
		return ;
	prev_x = coord.x;
	sx = 0;
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
	while (sx < (texture->h * texture->w))
	{
		screen_index = (coord.y * WIDTH + coord.x) * 4;
		put_pixel_from_img(texture->pixels + (sx * shift), doom, screen_index);
		coord.x++;
		sx++;
		if (sx % (texture->w) == 0)
		{
			coord.x = prev_x;
			coord.y++;
		}
	}
	return ;
}

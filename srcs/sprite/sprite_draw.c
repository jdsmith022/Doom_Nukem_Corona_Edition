/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:50:59 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/23 16:35:03 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index, int i)
{
	char	*pixels;
	char	*text;

	pixels = doom->surface->pixels;
	text = doom->lib.obj_lib[i]->pixels;
	if (text[pix_dex] != (char)255)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	if (text[pix_dex] != (char)255)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	if (text[pix_dex] != (char)255)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
}

int		find_tex_x(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp, int stripe)
{
	int		i_sprite;
	int		tex_x;

	i_sprite = doom->lib.sprites[index_sp].index;
	tex_x = 0;
	if (sprite_begin->x > 0 && sprite_begin->x < WIDTH)
		tex_x = (stripe - sprite_begin->x) / doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w;
	else
		tex_x = (sprite_end->x - stripe) / doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w;
	return (tex_x);
}

int		find_tex_y(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp, int stripe)
{
	int		i_sprite;
	int		tex_y;

	i_sprite = doom->lib.sprites[index_sp].index;
	tex_y = 0;
	if (sprite_begin->y > 0 && sprite_begin->y < HEIGHT)
		tex_y = (stripe - sprite_begin->y) / doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	else
		tex_y = (sprite_end->y - stripe) / doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	return (tex_y);
}

void	draw_stripes(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp)
{
	int		i_sprite;
	Uint32	index;
	Uint32	pix_dex;
	int		stripe;
	int		tex_y;
	int		tex_x;
	int		screen_y;

	i_sprite = doom->lib.sprites[index_sp].index;
	stripe = (int)sprite_begin->x/* + doom->pos.x*/;
	screen_y = (int)sprite_begin->y/* + doom->pos.y*/;
	index = 0;
	while (stripe < (int)sprite_end->x && stripe > 0 && stripe < WIDTH)
	{
		screen_y = (int)sprite_begin->y;
		tex_x = find_tex_x(doom, sprite_begin, sprite_end, index_sp, stripe);
		while (screen_y < (int)sprite_end->y/* && pix_y > 0 && pix_y < HEIGHT*/)
		{
			index = (size_t)(screen_y * doom->surface->pitch) + (int)(stripe * doom->surface->format->BytesPerPixel);
			tex_y = find_tex_y(doom, sprite_begin, sprite_end, index_sp, screen_y);
			pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch) + ((int)tex_x * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			//if stripe_distance[WIDTH] is niet kleiner dan sprite_distance op de x van de stripe
			put_pixel_tex(doom, pix_dex, index, i_sprite);
			screen_y++;
		}
		stripe++;
	}
}

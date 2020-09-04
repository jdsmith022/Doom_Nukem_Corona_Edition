/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:53:30 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/09/04 10:40:30 by rooscocolie   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"
#include "../../includes/hud.h"

void			put_pixel_tex(t_doom *doom, Uint32 pix_dex,\
			Uint32 index, int i)
{
	char	*pixels;
	char	*text;
	t_rgb	rgb;

	pixels = doom->surface->pixels;
	text = doom->lib.obj_lib[i]->pixels;
	rgb.r = text[pix_dex];
	rgb.g = text[pix_dex + 1];
	rgb.b = text[pix_dex + 2];
	if (text[pix_dex] == (char)255 && text[pix_dex + 1] == (char)255 &&\
	text[pix_dex + 2] == (char)255)
		;
	else
	{
		if (doom->lib.light > 0)
			add_saturation(&rgb.r, &rgb.g, &rgb.b,\
			doom->lib.light);
		pixels[index] = rgb.r;
		index++;
		pixels[index] = rgb.g;
		index++;
		pixels[index] = rgb.b;
	}
}

static int		find_x(t_doom *doom, t_line *sprite,\
		int index_sp, int stripe)
{
	int		i_sprite;
	int		tex_x;

	i_sprite = doom->lib.sprites[index_sp].visible;
	tex_x = 0;
	if ((int)sprite->start.x > 0 && sprite->start.x < WIDTH)
	{
		tex_x = (int)((stripe - (int)sprite->start.x) /\
		doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w);
	}
	else if ((int)sprite->start.x <= 0)
	{
		tex_x = (int)(((int)doom->lib.sprites[index_sp].width - sprite->end.x +\
		stripe) / (int)doom->lib.sprites[index_sp].width *\
		(int)doom->lib.obj_lib[i_sprite]->w);
	}
	else
	{
		tex_x = (int)((sprite->end.x - stripe) /\
		doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w);
	}
	return (tex_x);
}

static int		find_y(t_doom *doom, t_line *sprite, int index_sp, int screen_y)
{
	int		i_sprite;
	int		tex_y;

	i_sprite = doom->lib.sprites[index_sp].visible;
	tex_y = 0;
	if (sprite->start.y > 0)
		tex_y = (int)(screen_y - sprite->start.y) /\
		doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	else
	{
		tex_y = (int)(screen_y + (sprite->start.y * -1)) /\
		doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	}
	return (tex_y);
}

static void		put_stripe_sprite(t_doom *doom, int stripe, t_line *sprite,\
		int index_sp)
{
	Uint32		index;
	Uint32		pix_dex;
	t_coord		tex;
	int			screen_y;
	int			sprite_i;

	sprite_i = doom->lib.sprites[index_sp].visible;
	screen_y = (int)sprite->start.y;
	tex.x = find_x(doom, sprite, index_sp, stripe);
	while (screen_y < (int)sprite->end.y && screen_y < HEIGHT/* &&\
		no_clipping_region(screen_y, doom->lib.sprites[index_sp],\
		doom, stripe) == 1*/)
	{
		if (screen_y >= 0 /* && clip_top(doom, index_sp, stripe, screen_y) == -1*/)
		{
			index = (Uint32)(screen_y * doom->surface->pitch) +\
			(int)(stripe * doom->surface->format->BytesPerPixel);
			tex.y = find_y(doom, sprite, index_sp, screen_y);
			pix_dex = ((int)tex.y *\
			doom->lib.obj_lib[sprite_i]->pitch) + ((int)tex.x *\
			doom->lib.obj_lib[sprite_i]->format->BytesPerPixel);
			put_pixel_tex(doom, pix_dex, index, sprite_i);
		}
		screen_y++;
	}
}

void			draw_stripes(t_doom *doom, t_line *sprite, int index_sp)
{
	int			stripe;

	stripe = (int)sprite->start.x;
	while (stripe < (int)sprite->end.x && stripe >= 0 && stripe < WIDTH)
	{
		if (doom->stripe_distance[stripe] >\
		doom->lib.sprites[index_sp].distance)
		{
			sprite_light(doom, doom->lib.sprites[index_sp]);
			put_stripe_sprite(doom, stripe, sprite, index_sp);
		}
		stripe++;
	}
}

#include "../../includes/doom.h"
#include "../../includes/sprites.h"

void		put_pixel_tex2(t_doom *doom, Uint32 pix_dex,\
			Uint32 index, int index_sp)
{
	char	*pixels;
	char	*text;
	t_rgb	rgb;
	int		i;

	// i = get_lib_index(doom, index_sp); if index_sp == -1 then light == -1??
	i = doom->lib.sprites[index_sp].visible;
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
		if (doom->lib.sprites[index_sp].light > 0)
			add_saturation(&rgb.r, &rgb.g, &rgb.b,\
			doom->lib.sprites[index_sp].light);
		pixels[index] = rgb.r;
		index++;
		pixels[index] = rgb.g;
		index++;
		pixels[index] = rgb.b;
	}
}

void		put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index, int i,\
			double distance)
{
	char	*pixels;
	char	*text;
	Uint8	r;
	Uint8	g;
	Uint8	b;

	pixels = doom->surface->pixels;
	text = doom->lib.obj_lib[i]->pixels;
	r = text[pix_dex];
	g = text[pix_dex + 1];
	b = text[pix_dex + 2];
	if (text[pix_dex] == (char)255 && text[pix_dex + 1] == (char)255 &&\
	text[pix_dex + 2] == (char)255)
		;
	else
	{
		if (distance > 0)
			add_saturation(&r, &g, &b, distance);
		pixels[index] = r;
		index++;
		pixels[index] = g;
		index++;
		pixels[index] = b;
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

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int x)
{
	int		i;
	int		y_bottom;
	// int		y_top;
	int		mid_bottom;

	mid_bottom = 0;
	i = 0;
	while (i < sprite.n_sector)
	{
		mid_bottom =\
		doom->lib.sector[sprite.prev_sectors[i]].sidedef_mid_bottom[x];
		if (mid_bottom == -1)
			return (-1);
		y_bottom = doom->lib.sector[sprite.prev_sectors[i]].sidedef_bottom[x];
		if (y_bottom > 0 && y_bottom < HEIGHT && y_bottom < screen_y)
			return (-1);
		if (mid_bottom > 0 && mid_bottom < HEIGHT && mid_bottom < screen_y)
			return (-1);
		i++;
	}
	return (1);
}

void	sprite_light(t_doom *doom, t_sprite *sprite)
{
	if (doom->light == TRUE)
	{
		if (doom->lib.sector[sprite->sector].light == TRUE)
			sprite->light = doom->lib.sector[sprite->sector].light_level;
		else
			sprite->light = 0.15;
	}
	else
	{
		sprite->light = 1 / (sprite->distance / 70);
		sprite->light = sprite->sprite_x > WIDTH / 2 ? \
			sprite->light - (sprite->sprite_x - (float)WIDTH / 2.0) * 1.0 /\
			(float)WIDTH : + sprite->light - ((float)WIDTH / 2.0 -\
			sprite->sprite_x) * 1.0 / (float)WIDTH;
	}
}

void	draw_stripes(t_doom *doom, t_line *sprite, int index_sp)
{
	Uint32		index;
	Uint32		pix_dex;
	int			i_sprite;
	int			tex_y;
	int			tex_x;
	int			stripe;
	int			screen_y;
	double		light_dist;

	i_sprite = doom->lib.sprites[index_sp].visible;
	stripe = (int)sprite->start.x;
	screen_y = (int)sprite->start.y;
	index = 0;
	while (stripe < (int)sprite->end.x && stripe >= 0 && stripe < WIDTH)
	{
		if (doom->stripe_distance[stripe] >\
		doom->lib.sprites[index_sp].distance)
		{
			//volgens mij kan ik onderstaande functie ook later callen
			// sprite_light(doom, doom->lib.sprites[index_sp], &light_dist);
			sprite_light(doom, &doom->lib.sprites[index_sp]);
			screen_y = (int)sprite->start.y;
			tex_x = find_x(doom, sprite, index_sp, stripe);
			while (screen_y < (int)sprite->end.y && screen_y < HEIGHT &&\
				no_clipping_region(screen_y, doom->lib.sprites[index_sp],\
				doom, stripe) == 1)
			{
				if (screen_y >= 0)
				{
					index = (Uint32)(screen_y * doom->surface->pitch) +\
					(int)(stripe * doom->surface->format->BytesPerPixel);
					tex_y = find_y(doom, sprite, index_sp, screen_y);
					pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch)\
					+ ((int)tex_x *\
					doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
					put_pixel_tex2(doom, pix_dex, index, index_sp);
				}
				screen_y++;
			}
		}
		stripe++;
	}
}

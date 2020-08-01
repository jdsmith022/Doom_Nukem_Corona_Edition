#include "../../includes/doom.h"

void		put_pixel_tex(t_doom *doom, Uint32 pix_dex, Uint32 index, int i)
{
	char	*pixels;
	char	*text;

	pixels = doom->surface->pixels;
	text = doom->lib.obj_lib[i]->pixels;
	if (text[pix_dex] != (char)255 && text[pix_dex + 1] != (char)255 &&\
	text[pix_dex + 2] != (char)255)
	{
		pixels[index] = text[pix_dex];
		index++;
		pix_dex++;
		pixels[index] = text[pix_dex];
		index++;
		pix_dex++;
		pixels[index] = text[pix_dex];
	}
}

int		find_tex_x(t_doom *doom, t_point *sprite_begin, t_point *sprite_end,\
		int index_sp, int stripe)
{
	int		i_sprite;
	int		tex_x;

	i_sprite = doom->lib.sprites[index_sp].visible;
	tex_x = 0;
	if ((int)sprite_begin->x > 0 && sprite_begin->x < WIDTH)
	{
		tex_x = (stripe - (int)sprite_begin->x) /\
		doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w;
	}
	else if ((int)sprite_begin->x <= 0)
	{
		tex_x = ((int)doom->lib.sprites[index_sp].width - sprite_end->x +\
		stripe) / (int)doom->lib.sprites[index_sp].width *\
		(int)doom->lib.obj_lib[i_sprite]->w;
	}
	else
	{
		tex_x = (sprite_end->x - stripe) /\
		doom->lib.sprites[index_sp].width * doom->lib.obj_lib[i_sprite]->w;
	}
	return (tex_x);
}

int		find_tex_y(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp, int screen_y)
{
	int		i_sprite;
	int		tex_y;

	// i_sprite = doom->lib.sprites[index_sp].index;
	i_sprite = doom->lib.sprites[index_sp].visible; //multiple faces
	tex_y = 0;
	if (sprite_begin->y > 0 && sprite_begin->y < HEIGHT)
		tex_y = (int)(screen_y - sprite_begin->y) / doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	else
		tex_y = (int)(sprite_end->y - screen_y) / doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
	return (tex_y);
}

int		no_clipping_region(int screen_y, t_sprite sprite, t_doom *doom, int index_sp, int stripe)
{
	int		i;

	i = 0;
	if (sprite.n_sector > 0)
		// printf("sprite.n_sector: %d, sprite #%d\n", sprite.n_sector, index_sp);
	while (i < sprite.n_sector)
	{
		// printf("i: %d, prev_sector[i]: %d, stripe: %d\n", i, sprite.prev_sectors[i], stripe);
		if (doom->lib.sector[sprite.prev_sectors[i]].sidedef_bottom[stripe] > 0 &&\
		doom->lib.sector[sprite.prev_sectors[i]].sidedef_bottom[stripe] < HEIGHT &&\
		doom->lib.sector[sprite.prev_sectors[i]].sidedef_bottom[stripe] < screen_y)
			return (-1);
		i++;
	}
	return (1);
}

void	draw_stripes(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp)
{
	int			i_sprite;
	Uint32		index;
	Uint32		pix_dex;
	int			stripe;
	int			tex_y;
	int			tex_x;
	int			screen_y;
	t_sprite	sprite;

	sprite = doom->lib.sprites[index_sp];
	i_sprite = doom->lib.sprites[index_sp].visible;
	stripe = (int)sprite_begin->x;
	screen_y = (int)sprite_begin->y;
	index = 0;
	while (stripe < (int)sprite_end->x && stripe >= 0 && stripe < WIDTH)
	{
		if (doom->stripe_distance[stripe] > doom->lib.sprites[index_sp].distance)
		{
			screen_y = (int)sprite_begin->y;
			tex_x = find_tex_x(doom, sprite_begin, sprite_end, index_sp, stripe);
			while (screen_y < (int)sprite_end->y  && no_clipping_region(screen_y, sprite, doom,\
			index_sp, stripe) == 1)
			{
				index = (size_t)(screen_y * doom->surface->pitch) + (int)(stripe * doom->surface->format->BytesPerPixel);
				tex_y = find_tex_y(doom, sprite_begin, sprite_end, index_sp, screen_y);
				pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch) + ((int)tex_x * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
				put_pixel_tex(doom, pix_dex, index, i_sprite);

				screen_y++;
			}
		}
		stripe++;
	}
}

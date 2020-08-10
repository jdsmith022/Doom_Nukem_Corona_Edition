#include "../../includes/doom.h"

void		scale_bar(t_doom *doom, t_point *bar_begin, t_point *bar_end)
{
	double	bar_height;
	double	bar_width;
	double	h;
	double	w;

	bar_end->y = HEIGHT - 55;
	bar_height = HEIGHT / 3 * 2;
	bar_begin->y = bar_end->y - bar_height;
	h = doom->lib.obj_lib[28]->h;
	w = doom->lib.obj_lib[28]->w;
	bar_width = (bar_height / h) * w;
	bar_begin->x = (WIDTH / 2) - (bar_width / 2);
	bar_end->x = bar_begin->x + bar_width;
}

int		find_x_bar(t_doom *doom, t_point *sprite_begin, t_point *sprite_end,\
		int stripe)
{
	int		i_sprite;
	int		tex_x;
	double	width;

	width = sprite_end->x - sprite_begin->x;
	i_sprite = 28;
	tex_x = 0;
	if ((int)sprite_begin->x > 0 && sprite_begin->x < WIDTH)
	{
		tex_x = (int)((stripe - (int)sprite_begin->x) /\
		width * doom->lib.obj_lib[i_sprite]->w);
	}
	else if ((int)sprite_begin->x <= 0)
	{
		tex_x = (int)(((int)width - sprite_end->x +\
		stripe) / (int)width *\
		(int)doom->lib.obj_lib[i_sprite]->w);
	}
	else
	{
		tex_x = (int)((sprite_end->x - stripe) /\
		width * doom->lib.obj_lib[i_sprite]->w);
	}
	return (tex_x);
}

int		find_y_bar(t_doom *doom, t_point *sprite_begin, t_point *sprite_end,\
		int screen_y)
{
	int		i_sprite;
	int		tex_y;
	double	height;

	height = sprite_end->y - sprite_begin->y;
	i_sprite = 28;
	tex_y = 0;
	if (sprite_begin->y > 0 && sprite_begin->y < HEIGHT)
		tex_y = (int)(screen_y - sprite_begin->y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	else
		tex_y = (int)(sprite_end->y - screen_y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	return (tex_y);
}

void		draw_stripes_bar(t_doom *doom, t_point bar_begin, t_point bar_end)
{
	int			i_sprite;
	Uint32		index;
	Uint32		pix_dex;
	int			stripe;
	int			tex_y;
	int			tex_x;
	int			screen_y;
	t_sprite	sprite;

	sprite = doom->lib.sprites[doom->save_scissor_lift];
	i_sprite = 28;
	stripe = (int)bar_begin.x;
	screen_y = (int)bar_begin.y;
	index = 0;
	while (stripe < (int)bar_end.x && stripe >= 0 && stripe < WIDTH)
	{
		screen_y = (int)bar_begin.y;
		tex_x = find_x_bar(doom, &bar_begin, &bar_end, stripe);
		while (screen_y < (int)bar_end.y)
		{
			index = (Uint32)(screen_y * doom->surface->pitch) +\
			(int)(stripe * doom->surface->format->BytesPerPixel);
			tex_y = find_y_bar(doom, &bar_begin, &bar_end,\
			screen_y);
			pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch)\
			+ ((int)tex_x *\
			doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			put_pixel_tex(doom, pix_dex, index, i_sprite, 0);
			screen_y++;
		}
		stripe++;
	}
}

void		draw_scissor_lift_bar(t_doom *doom)
{
	t_point bar_begin;
	t_point	bar_end;

	scale_bar(doom, &bar_begin, &bar_end);
	draw_stripes_bar(doom, bar_begin, bar_end);
}

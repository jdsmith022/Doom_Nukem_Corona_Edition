#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"

void		scale_bar(t_doom *doom, t_point *bar_begin,
					t_point *bar_end, int i)
{
	double	bar_height;
	double	bar_width;
	double	h;
	double	w;

	bar_end->y = HEIGHT - 55;
	if (i == SCISSOR)
		bar_height = HEIGHT / 3 * 2;
	else if (i == 76)
		bar_height = HEIGHT / 16;
	else
		bar_height = HEIGHT / 2;
	bar_begin->y = bar_end->y - bar_height;
	h = doom->lib.obj_lib[i]->h;
	w = doom->lib.obj_lib[i]->w;
	bar_width = (bar_height / h) * w;
	if (i == SCISSOR || i == CROSS_HAIR)
		bar_begin->x = (WIDTH / 2) - (bar_width / 2);
	else
		bar_begin->x = 10;
	bar_end->x = bar_begin->x + bar_width;
}

static int		find_x_bar(t_doom *doom, t_point *sprite_begin, t_point *sprite_end,\
					int stripe, int i_sprite)
{
	int		tex_x;
	double	width;

	width = sprite_end->x - sprite_begin->x;
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

static int		find_y_bar(t_doom *doom, t_point *sprite_begin, \
                    t_point *sprite_end, int screen_y, int i_sprite)
{
	int		tex_y;
	double	height;

	height = sprite_end->y - sprite_begin->y;
	tex_y = 0;
	if (sprite_begin->y > 0 && sprite_begin->y < HEIGHT)
		tex_y = (int)(screen_y - sprite_begin->y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	else
		tex_y = (int)(sprite_end->y - screen_y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	return (tex_y);
}

void		    draw_stripes_bar(t_doom *doom, t_point bar_begin,
					t_point bar_end, int i_sprite)
{
	Uint32		index;
	Uint32		pix_dex;
	int			stripe;
	int			tex_y;
	int			tex_x;
	int			screen_y;

	stripe = (int)bar_begin.x;
	screen_y = (int)bar_begin.y;
	index = 0;
	while (stripe < (int)bar_end.x && stripe >= 0 && stripe < WIDTH)
	{
		screen_y = (int)bar_begin.y;
		tex_x = find_x_bar(doom, &bar_begin, &bar_end, stripe, i_sprite);
		while (screen_y < (int)bar_end.y)
		{
			index = (Uint32)(screen_y * doom->surface->pitch) +\
			(int)(stripe * doom->surface->format->BytesPerPixel);
			tex_y = find_y_bar(doom, &bar_begin, &bar_end,\
			screen_y, i_sprite);
			pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch)\
			+ ((int)tex_x *\
			doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			put_pixel_tex(doom, pix_dex, index, i_sprite, -1);
			screen_y++;
		}
		stripe++;
	}
}
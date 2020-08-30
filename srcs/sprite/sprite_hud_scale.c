/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_hud_scale.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: rsteigen <rsteigen@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/30 21:54:17 by rsteigen      #+#    #+#                 */
/*   Updated: 2020/08/30 21:54:19 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/sprites.h"

void		scale_bar(t_doom *doom, t_line *bar, int i)
{
	double	bar_height;
	double	bar_width;
	double	h;
	double	w;

	bar->end.y = HEIGHT - 55;
	if (i == SCISSOR)
		bar_height = HEIGHT / 3 * 2;
	else if (i == 76)
		bar_height = HEIGHT / 16;
	else
		bar_height = HEIGHT / 2;
	bar->start.y = bar->end.y - bar_height;
	h = doom->lib.obj_lib[i]->h;
	w = doom->lib.obj_lib[i]->w;
	bar_width = (bar_height / h) * w;
	if (i == SCISSOR || (i == CROSS_HAIR && doom->player_handed == left))
		bar->start.x = (WIDTH / 2) - (bar_width / 2);
	else if (i == CROSS_HAIR && doom->player_handed == right)
		bar->start.x = WIDTH / 2 - 20;
	else
		bar->start.x = 10;
	bar->end.x = bar->start.x + bar_width;
}

static int		find_x_bar(t_doom *doom, t_line *bar,\
				int stripe, int i_sprite)
{
	int		tex_x;
	double	width;

	width = bar->end.x - bar->start.x;
	tex_x = 0;
	if ((int)bar->start.x > 0 && bar->start.x < WIDTH)
	{
		tex_x = (int)((stripe - (int)bar->start.x) /\
		width * doom->lib.obj_lib[i_sprite]->w);
	}
	else if ((int)bar->start.x <= 0)
	{
		tex_x = (int)(((int)width - bar->end.x +\
		stripe) / (int)width *\
		(int)doom->lib.obj_lib[i_sprite]->w);
	}
	else
	{
		tex_x = (int)((bar->end.x - stripe) /\
		width * doom->lib.obj_lib[i_sprite]->w);
	}
	return (tex_x);
}

static int		find_y_bar(t_doom *doom, t_line *bar,\
				int screen_y, int i_sprite)
{
	int		tex_y;
	double	height;

	height = bar->end.y - bar->start.y;
	tex_y = 0;
	if (bar->start.y > 0 && bar->start.y < HEIGHT)
		tex_y = (int)(screen_y - bar->start.y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	else
		tex_y = (int)(bar->end.y - screen_y) /\
		height * doom->lib.obj_lib[i_sprite]->h;
	return (tex_y);
}

static void		put_stripe_bar(t_doom *doom, int stripe,\
				t_line bar, int i_sprite)
{
	int			screen_y;
	t_coord		tex;
	Uint32		index;
	Uint32		pix_dex;

	screen_y = (int)bar.start.y;
	tex.x = find_x_bar(doom, &bar, stripe, i_sprite);
	while (screen_y < (int)bar.end.y)
	{
		index = (Uint32)(screen_y * doom->surface->pitch) +\
		(int)(stripe * doom->surface->format->BytesPerPixel);
		tex.y = find_y_bar(doom, &bar, screen_y, i_sprite);
		pix_dex = ((int)tex.y * doom->lib.obj_lib[i_sprite]->pitch)\
		+ ((int)tex.x *\
		doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
		put_pixel_tex(doom, pix_dex, index, i_sprite);
		screen_y++;
	}
}

void			draw_stripes_bar(t_doom *doom, t_line bar, int i_sprite)
{
	int			stripe;

	stripe = (int)bar.start.x;
	doom->lib.light = -1;
	while (stripe < (int)bar.end.x && stripe >= 0 && stripe < WIDTH)
	{
		put_stripe_bar(doom, stripe, bar, i_sprite);
		stripe++;
	}
}

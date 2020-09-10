/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_map_sprite.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 15:13:48 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void			put_pixel_object(t_doom *doom, int x, int y, int color)
{
	Uint32 *pixels;

	pixels = doom->surface->pixels;
	if (x >= SIDEBAR_SECTOR && x <= SIDEBAR_SIDEDEF && y >= 0 && y <= HEIGHT)
		pixels[(y * WIDTH + x)] = color;
}

static void			draw_sprite_pos(t_doom *doom, Uint32 **pixels,
						t_ed_sprite *sprite, int side)
{
	double			i;
	int				color;
	int				x;
	int				y;
	t_line			line[4];

	i = 0.0;
	if (doom->game_design.cur_sprite != sprite->id || \
	doom->game_design.object_bar == 0)
		color = 0x8c3cde6;
	else
		color = 0xff4287f5;
	x = sprite->pos.x - 5;
	y = sprite->pos.y - 5;
	while (x < sprite->pos.x + 5)
	{
		y = sprite->pos.y - 5;
		while (y < sprite->pos.y + 5)
		{
			put_pixel_object(doom, x, y, color);
			y++;
		}
		x++;
	}
}

void				draw_ed_sprite(t_doom *doom, Uint32 **pixels)
{
	t_ed_sprite	*sprite;
	int			side;

	sprite = doom->game_design.sp_head->next;
	while (sprite != NULL)
	{
		draw_sprite_pos(doom, pixels, sprite, side);
		sprite = sprite->next;
	}
}

void		highlight_curr_sector(t_doom *doom)
{
	t_line		bound;
	t_point		pixel;

	bound = sc_lines[doom->game_design.i_sector];
	pixel.x = bound.start.x;
	while (pixel.x < bound.end.x)
	{
		// printf("color??\n");
		pixel.y = bound.start.y;
		while (pixel.y < bound.end.y)
		{
			put_pixel_object(doom, pixel.x, pixel.y, 0x7e7f81);
			pixel.y++;
		}
		pixel.x++;
	}
}

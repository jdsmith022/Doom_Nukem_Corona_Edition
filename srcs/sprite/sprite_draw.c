/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:50:59 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/08 17:03:22 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/doom.h"

void		put_pixel_tex(t_doom *doom, Uint32 pix_dex, size_t index, int i)
{
	char	*pixels;
	char	*text;

	pixels = doom->surface->pixels;
	text = doom->sprite_image[i]->pixels;
	if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
}

void	draw_stripes(t_doom *doom, t_point sprite_cord, int index_sp)
{
	int		i_sprite;
	t_point	begin;
	t_point	end;
	size_t	index;
	Uint32	pix_dex;
	int		stripe;
	int		pix_y;
	int		pix_x;
	int		screen_y;

	printf("BEGIN DRAW STRIPES\n");
	i_sprite = doom->lib.sprite[index_sp].index;
	begin.x = sprite_cord.x - doom->lib.sprite[index_sp].width / 2;
	begin.y = sprite_cord.y - doom->lib.sprite[index_sp].height / 2;
	end.x = begin.x + doom->lib.sprite[index_sp].width;
	end.y = begin.y + doom->lib.sprite[index_sp].height;
	stripe = begin.x;
	pix_y = 0;
	pix_x = 0;
	screen_y = begin.y;
	index = 0;
	while (stripe < end.x && begin.x > 0 && stripe < WIDTH)
	{
		printf("inside while level1\n");
		pix_y = 0;
		screen_y = (int)begin.y;
		printf("pix_y: %d, < end.y: %d\n", pix_y, (int)end.y);
		while (pix_y < (int)end.y/* && pix_y > 0 && pix_y < HEIGHT*/)
		{
			printf("inside while level2\n");
			index = (screen_y * doom->surface->pitch) + (stripe + doom->surface->format->BytesPerPixel);
			pix_dex = (pix_y * doom->lib.obj_lib[i_sprite]->pitch) + (pix_x * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			put_pixel_tex(doom, pix_dex, index, i_sprite);
			pix_y++;
			screen_y++;
		}
		pix_x++;
		stripe++;
	}
}

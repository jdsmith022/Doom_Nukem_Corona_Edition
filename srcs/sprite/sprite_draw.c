/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sprite_draw.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rooscocolien <rooscocolien@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 15:50:59 by rooscocolie   #+#    #+#                 */
/*   Updated: 2020/07/18 18:26:21 by rsteigen      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

void		put_pixel_tex(t_doom *doom, Uint32 pix_dex, size_t index, int i)
{
	char	*pixels;
	char	*text;

	pixels = doom->surface->pixels;
	text = doom->lib.obj_lib[i]->pixels;
	// if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	// if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
	// if (text[pix_dex] != 0)
		pixels[index] = text[pix_dex];
	index++;
	pix_dex++;
}

void	draw_stripes(t_doom *doom, t_point *sprite_begin, t_point *sprite_end, int index_sp)
{
	int		i_sprite;
	// t_point	begin;
	// t_point	end;
	size_t	index;
	Uint32	pix_dex;
	int		stripe;
	// double	tex_x;
	double	tex_y;
	double	pix_y;
	double	y;
	double	x;
	double	y_temp;
	double	x_temp;
	// int		pix_x;
	double	screen_y;

	// printf("BEGIN DRAW STRIPES\n");
	i_sprite = doom->lib.sprites[index_sp].index;
	// begin.x = sprite_cord.x - doom->lib.sprites[index_sp].width / 2;
	// begin.y = sprite_cord.y - doom->lib.sprites[index_sp].height / 2;
	// end.x = begin.x + doom->lib.sprites[index_sp].width;
	// end.y = begin.y + doom->lib.sprites[index_sp].height;
	// printf("%f; %f\t%f; %f\n", begin.x, begin.y, end.x, end.y);
	stripe = (int)sprite_begin->x;
	// pix_x = 0;
	screen_y = (int)sprite_begin->y;
	index = 0;
	x = 0;
	x_temp = 0;
	// tex_x = 0;
	while (stripe < (int)sprite_end->x && stripe > 0 && stripe < WIDTH)
	{
		// pix_y = 0;
		// tex_y = 0;
		tex_y = tex_y / doom->lib.sprites[index_sp].height * doom->lib.obj_lib[i_sprite]->h;
		y = 0;
		y_temp = 0;
		screen_y = (int)sprite_begin->y;
		// printf("pix_y: %d, < end.y: %d\n", pix_y, (int)end.y);
		if (x != 0)
			x_temp = (double)(stripe - (int)sprite_begin->x) / doom->lib.sprites[index_sp].width * x;
		while (screen_y < (int)sprite_end->y/* && pix_y > 0 && pix_y < HEIGHT*/)
		{
			index = (size_t)(screen_y * doom->surface->pitch) + (int)(stripe * doom->surface->format->BytesPerPixel);
			// pix_dex = ((int)tex_y * doom->lib.obj_lib[i_sprite]->pitch) + (tex_x * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			// pix_y = (double)(64 / doom->lib.sprites[index_sp].height) * ((double)(screen_y + stripe) /* + off_set*/ - begin.y);
			// pix_dex = ((int)pix_y * doom->lib.obj_lib[i_sprite]->pitch) + (stripe * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			//CONSIDER SIZE OF THE TEXTURE
			if (y != 0)
				y_temp = (double)(screen_y - (int)sprite_begin->y) / doom->lib.sprites[index_sp].height * y;
			// printf("(x: %f; y: %f) (x_temp: %f;y_temp: %f) width: %f", x, y, x_temp, y_temp, doom->lib.sprites[index_sp].width);
			pix_dex = ((int)y_temp * doom->lib.obj_lib[i_sprite]->pitch) + ((int)x_temp * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			//if stripe_distance[WIDTH] is niet kleiner dan sprite_distance op de x van de stripe
			put_pixel_tex(doom, pix_dex, index, i_sprite);
			// pix_y++;
			y++;
			screen_y++;
			tex_y++;
		}
		// printf("screen_y: %f, end.y: %f\n", screen_y, end.y);
		// printf("stripe: %d, end.x: %f\n", stripe, end.x);
		// pix_x++;
		// tex_x++;
		stripe++;
		x++;
	}
}

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

void	draw_stripes(t_doom *doom, t_point sprite_cord, int index_sp)
{
	int		i_sprite;
	t_point	begin;
	t_point	end;
	size_t	index;
	Uint32	pix_dex;
	int		stripe;
	double	pix_y;
	// int		pix_x;
	double	screen_y;

	printf("BEGIN DRAW STRIPES\n");
	i_sprite = doom->lib.sprites[index_sp].index;
	begin.x = sprite_cord.x - doom->lib.sprites[index_sp].width / 2;
	begin.y = sprite_cord.y - doom->lib.sprites[index_sp].height / 2;
	end.x = begin.x + doom->lib.sprites[index_sp].width;
	end.y = begin.y + doom->lib.sprites[index_sp].height;
	printf("%f; %f\t%f; %f\n", begin.x, begin.y, end.x, end.y);
	stripe = begin.x;
	// pix_x = 0;
	screen_y = begin.y;
	index = 0;
	while (stripe < end.x && stripe > 0 && stripe < WIDTH)
	{
		// printf("inside while level1\n");
		// pix_y = 0;
		screen_y = (int)begin.y;
		// printf("pix_y: %d, < end.y: %d\n", pix_y, (int)end.y);
		while (screen_y < (int)end.y/* && pix_y > 0 && pix_y < HEIGHT*/)
		{
			// printf("inside while level2\n");
			index = (screen_y * doom->surface->pitch) + (int)(stripe * doom->surface->format->BytesPerPixel);
			pix_y = (double)(64 / doom->lib.sprites[index_sp].height) * ((double)(screen_y + stripe)  /*+ off_set*/ - begin.y);
			pix_dex = ((int)pix_y * doom->lib.obj_lib[i_sprite]->pitch) + (stripe * doom->lib.obj_lib[i_sprite]->format->BytesPerPixel);
			//if stripe_distance[WIDTH] is niet kleiner dan sprite_distance op de x van de stripe
			put_pixel_tex(doom, pix_dex, index, i_sprite);
			// pix_y++;
			screen_y++;
		}
		printf("screen_y: %f, end.y: %f\n", screen_y, end.y);
		printf("stripe: %d, end.x: %f\n", stripe, end.x);
		// pix_x++;
		stripe++;
	}
}
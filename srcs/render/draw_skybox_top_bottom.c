#include "../../includes/doom.h"

static void		put_row(t_doom *doom, Uint32 tex_dex,
					Uint32 index, Uint64 pixel_dex)
{
	char *pixels;
	char *texture;

	pixels = doom->surface->pixels;
	texture = doom->lib.sky_lib[tex_dex]->pixels;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
}

static void		row_calculations(t_doom *doom, double dist, Uint32 index,
					Uint32 tex_dex)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = doom->lib.sky_lib[tex_dex]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += 32;
	floor.y += 32 * 3000;
	texture.x = ((int)floor.x % doom->texture_width);
	texture.y = ((int)floor.y % doom->texture_height);
	pixel_dex = ((int)texture.y * doom->lib.sky_lib[tex_dex]->pitch)\
		+ ((int)texture.x * bpp);
	put_row(doom, tex_dex, index, pixel_dex);
}

void			draw_ground(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint32	tex_dex;
	Uint8	bpp;

	tex_dex = 1;
	height = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / ((y + doom->own_event.y_pitch) - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}

void			draw_sky(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint32	height;
	Uint8	bpp;

	tex_dex = 0;
	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	while (y >= 0)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height / (height - (y + doom->own_event.y_pitch)) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_calculations(doom, dist, index, tex_dex);
		y--;
	}
}

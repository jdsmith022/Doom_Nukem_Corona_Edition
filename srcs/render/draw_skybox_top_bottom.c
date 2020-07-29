#include "../../includes/doom.h"

static void		put_sky(t_doom *doom, SDL_Surface *lib,
					Uint32 index, Uint64 pixel_dex)
{
	char *pixels;
	char *texture;

	pixels = doom->surface->pixels;
	texture = lib->pixels;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
	index++;
	pixel_dex++;
	pixels[index] = texture[pixel_dex];
}

static void		row_cal(t_doom *doom, double dist, Uint32 index,
					SDL_Surface *lib)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = lib->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += 32 * 2;
	floor.y += 32 * 2;
	texture.x = ((int)floor.x % doom->texture_width);
	texture.y = ((int)floor.y % doom->texture_width);
	pixel_dex = ((int)texture.y * lib->pitch)\
		+ ((int)texture.x * bpp);
	put_sky(doom, lib, index, pixel_dex);
}

void			draw_ground(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint8	bpp;

	doom->tex_dex = 1;
	height = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	while (y < HEIGHT)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height /\
			((y + doom->own_event.y_pitch) - height) * (doom->dist_to_plane);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_cal(doom, dist, index, doom->lib.sky_lib[doom->tex_dex]);
		y++;
	}
}

void			draw_sky(t_doom *doom, int x, int y)
{
	double	dist;
	Uint32	index;
	Uint32	height;
	Uint8	bpp;

	doom->tex_dex = 0;
	bpp = doom->surface->format->BytesPerPixel;
	height = (HEIGHT + doom->player_height) / 2;
	while (y >= 0)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = doom->player_std_height /\
			(height - (y + doom->own_event.y_pitch)) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		row_cal(doom, dist, index, doom->lib.sky_lib[doom->tex_dex]);
		y--;
	}
}

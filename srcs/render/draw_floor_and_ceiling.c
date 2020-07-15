#include "../../includes/doom.h"

static void		put_row(t_doom *doom, Uint32 tex_dex,
					Uint32 index, Uint64 pixel_dex)
{
	char *pixels;
	char *texture;
	char	R;
	char	G;
	char	B;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	R = texture[pixel_dex];
	G = texture[pixel_dex + 1];
	B = texture[pixel_dex + 2];
	add_saturation(&R, &G, &B, doom->distance);
	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	pixels[index] = R;
	index++;
	pixels[index] = G;
	index++;
	pixels[index] = B;
}

static void		row_calculations(t_doom *doom, double dist, Uint32 index,
					Uint32 tex_dex)
{
	t_point	texture;
	t_point	floor;
	Uint64	pixel_dex;
	Uint8	bpp;

	bpp = doom->lib.tex_lib[tex_dex]->format->BytesPerPixel;
	floor.x = dist * cos(doom->ray_angle);
	floor.y = dist * sin(doom->ray_angle);
	floor.x += doom->pos.x;
	floor.y += doom->pos.y;
	texture.x = (int)floor.x % 96;
	texture.y = (int)floor.y % 96;
	pixel_dex = (((int)texture.y * doom->lib.tex_lib[tex_dex]->pitch)\
		+ ((int)texture.x * bpp));
	put_row(doom, tex_dex, index, pixel_dex);
}

void			add_filter(t_doom *doom, int y, int filter, int index)
{
	char *pixels;
	pixels = doom->surface->pixels;

	if (filter != 0)
		pixels[index] += filter;
}

void			draw_ceiling(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int limit;

	tex_dex = sector.txt_ceiling;
	bpp = doom->surface->format->BytesPerPixel;
	doom->mid_screen = (HEIGHT + doom->player_height) / 2;
	limit = 0;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_ceiling;
	while (y >= limit)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = (doom->player_std_height - sector.height_ceiling)\
			/ (doom->mid_screen - y) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		if (doom->light == TRUE)
		{
			if (sector.light == TRUE)
				doom->distance = sector.light_level;
			else
				doom->distance = 0.15;
		}
		else
		{
			doom->distance = dist;
			doom->distance = 1 / ((float)doom->distance / 70.0);
			doom->distance = x > WIDTH / 2 ? doom->distance - (x - (float)WIDTH / 2.0) * X_CHANGE : + doom->distance - ((float)WIDTH / 2.0 - x) * X_CHANGE;
			doom->distance = y > HEIGHT / 2 ? doom->distance - (y - (float)HEIGHT / 2.0) * Y_CHANGE : + doom->distance - ((float)HEIGHT/ 2.0 - y) * Y_CHANGE;
		}
		row_calculations(doom, dist, index, tex_dex);
		y--;
	}
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int 	limit;

	tex_dex = sector.txt_floor;
	doom->mid_screen = (HEIGHT + doom->player_height) / 2;
	bpp = doom->surface->format->BytesPerPixel;
	limit = HEIGHT;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_floor;
	while (y < limit)
	{
		index = (y * doom->surface->pitch) + (x  * bpp);
		dist = (doom->player_std_height - sector.height_floor)\
			/ (y - doom->mid_screen) * doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		if (doom->light == TRUE)
		{
			if (sector.light == TRUE)
				doom->distance = sector.light_level;
			else
				doom->distance = 0.15;
		}
		else
		{
			doom->distance = dist;
			doom->distance = 1 / ((float)doom->distance / 70.0);
			doom->distance = x > WIDTH / 2 ? doom->distance - (x - (float)WIDTH / 2.0) * X_CHANGE : + doom->distance - ((float)WIDTH / 2.0 - x) * X_CHANGE;
			doom->distance = y > HEIGHT / 2 ? doom->distance - (y - (float)HEIGHT / 2.0) * Y_CHANGE : + doom->distance - ((float)HEIGHT/ 2.0 - y) * Y_CHANGE;
		}
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}

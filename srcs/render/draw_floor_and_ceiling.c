#include "../../includes/doom.h"

static void		put_row(t_doom *doom, Uint32 tex_dex,
					Uint32 index, Uint64 pixel_dex)
{
	char	*pixels;
	char	*texture;
	char	r;
	char	g;
	char	b;

	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	r = texture[pixel_dex];
	g = texture[pixel_dex + 1];
	b = texture[pixel_dex + 2];
	add_saturation(&r, &g, &b, doom->distance);
	pixels = doom->surface->pixels;
	texture = doom->lib.tex_lib[tex_dex]->pixels;
	pixels[index] = r;
	index++;
	pixels[index] = g;
	index++;
	pixels[index] = b;
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
	texture.x = (int)floor.x % doom->texture_width;
	texture.y = (int)floor.y % doom->texture_height;
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
	int		limit;

	tex_dex = sector.txt_ceiling;
	bpp = doom->surface->format->BytesPerPixel;
	limit = 0;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_ceiling;
	while (y >= limit)
	{
		index = (y * doom->surface->pitch) + (x * bpp);
		dist = (doom->player_std_height - sector.height_ceiling)\
			/ ((HEIGHT / 2 + doom->player_height)\
			- (y + doom->own_event.y_pitch));
		dist *= doom->dist_to_plane;
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		doom->horizontal_plane_dist = dist;
		light_floor_ceiling(doom, sector, x, y);
		row_calculations(doom, dist, index, tex_dex);
		y--;
	}
}

double			set_slope_delta(t_doom *doom, t_sector sector, int y)
{
	double		height_diff;
	double		distance;
	double		height;
	double		delta_height;
	double		delta_steps;

	height_diff = sector.slope.bottom_height - sector.slope.height;
	delta_height = height_diff / sector.slope.distance;
	delta_steps = sector.slope.bottom_plane - y;
	delta_height = height_diff / delta_steps;
	if (sector.slope.sidedef_id == 10)
		printf("delta_heigth = %f | plane.end = %d | plane_start = %d | slope_height = %f\n\n", delta_height, sector.slope.bottom_plane, y, sector.slope.height);
	delta_height = 0;
	return (delta_height);
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int		limit;
	double	delta_height;

	tex_dex = sector.txt_floor;
	bpp = doom->surface->format->BytesPerPixel;
	limit = HEIGHT;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_floor;
	if (sector.slope_id != -1)
	{
		limit = sector.slope.bottom_plane;
		delta_height = set_slope_delta(doom, sector, y);
	}
	while (y < limit)
	{
		dist = ((doom->player_std_height - sector.height_floor)\
			/ ((y + doom->own_event.y_pitch) -\
			((HEIGHT / 2) + doom->player_height)));
		if (sector.slope_id != -1)
		{
			sector.height_floor += delta_height;
			if (sector.slope.sidedef_id == 10)
				printf("%d -- %f\n", y, sector.height_floor);
		}
		dist *= doom->dist_to_plane;
		index = (y * doom->surface->pitch) + (x * bpp);
		dist /= cos(doom->ray_adjacent * x - FOV / 2);
		doom->horizontal_plane_dist = dist;
		light_floor_ceiling(doom, sector, x, y);
		row_calculations(doom, dist, index, tex_dex);
		y++;
	}
}

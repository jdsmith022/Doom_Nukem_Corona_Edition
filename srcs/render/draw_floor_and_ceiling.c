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

double			set_new_height(t_doom *doom, t_sector *sector)
{
	double		height;
	t_point		intersect;
	double		distance;
	t_line		slope_id;

	intersect.x = sector->slope.intersect.x;
	intersect.y = sector->slope.intersect.y--;
	slope_id = doom->lib.sidedef[sector->slope_id].line;
	distance = fabs(point_line_distance(intersect, slope_id));
	return (tan(sector->slope_floor) * distance);
}

void			draw_floor(t_doom *doom, int x,
					t_sector sector, int y)
{
	double	dist;
	Uint32	index;
	Uint32	tex_dex;
	Uint8	bpp;
	int		limit;

	tex_dex = sector.txt_floor;
	bpp = doom->surface->format->BytesPerPixel;
	limit = HEIGHT;
	if (doom->lib.sector[doom->prev_sector].outside)
		limit = doom->lib.portal_floor;
	if (sector.slope_id != -1)
		limit = sector.slope.plane_end;
	while (y < limit)
	{
		dist = ((doom->player_std_height - sector.height_floor)\
			/ ((y + doom->own_event.y_pitch) -\
			((HEIGHT / 2) + doom->player_height)));
		if (sector.slope_id != -1)
		{
			sector.height_floor = set_new_height(doom, &sector);
			printf("%f\n", sector.height_floor);
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

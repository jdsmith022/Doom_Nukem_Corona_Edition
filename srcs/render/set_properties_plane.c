#include "../../includes/doom.h"

// static void	set_plane_limits(int *top, )

static int	set_plane_bottom(t_doom *doom, double scale, double distance, int sector_floor)
{
	double	height_floor;
	int		sidedef_bottom;
	

	height_floor = sector_floor / distance * doom->dist_to_plane;
	sidedef_bottom = ((HEIGHT / 2) + ((doom->player_height) * scale)) - (doom->own_event.y_pitch + height_floor);
	if (sidedef_bottom < 0)
		sidedef_bottom = 0;
	else if (sidedef_bottom > HEIGHT)
		sidedef_bottom = HEIGHT;
	return (sidedef_bottom);
}

static int set_plane_top(t_doom *doom, double scale, double distance, int sector_ceiling)
{
	double 	height_ceiling;
	int		sidedef_top;
	int 	diff;

	diff = STD_TEXT - doom->player_height;
	height_ceiling = sector_ceiling / distance * doom->dist_to_plane;
	sidedef_top = ((HEIGHT / 2) - (diff * scale)) - (doom->own_event.y_pitch + height_ceiling);
	return (sidedef_top);
}

void        set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
                    t_sector opp_sector, t_plane *plane)
{
    double      height_floor;
    double      height_ceiling;
    int         mid_top;
    int         mid_bottom;
    int         new_height;

    if (opp_sector.slope_floor_id != -1)
        set_slope_height(doom, sidedef, opp_sector);
    double diff = doom->texture_height - doom->player_height;
    new_height = (HEIGHT / 2);
    plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
    double scale =  plane->height_standard / doom->texture_height;
    height_ceiling = opp_sector.height_ceiling / sidedef.distance * doom->dist_to_plane;
    mid_top = ((new_height) - (diff * scale)) - (doom->own_event.y_pitch + height_ceiling);
    height_floor = opp_sector.height_floor / sidedef.distance * doom->dist_to_plane;
    mid_bottom = (new_height + ((doom->player_height) * scale)) - (doom->own_event.y_pitch + height_floor);
    if (mid_bottom < 0)
        mid_bottom = 0;
    if ( mid_top > HEIGHT)
        mid_top = HEIGHT;
    else if (mid_top < 0)
        mid_top = 0;
    plane->mid_texture_top = mid_top;
    // printf(“mid_bottom: %d\n”, mid_bottom);
    plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT));
}


void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		height_floor;
	double		scale;
	int			sidedef_bottom;

	if (sector.slope_floor_id != -1)
		sector.height_floor += set_slope_height(doom, sidedef, sector);
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	scale =  plane->height_standard / doom->texture_height;
	plane->sidedef_top = set_plane_top(doom, scale, sidedef.distance, sector.height_ceiling);
	wall_offset(plane, plane->sidedef_top);
	plane->sidedef_bottom = set_plane_bottom(doom, scale, sidedef.distance, sector.height_floor);
}

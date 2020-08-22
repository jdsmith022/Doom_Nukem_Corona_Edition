#include "../../includes/doom.h"

static void		set_sector_properties(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	t_sector opp_sector;

	if (sidedef.opp_sector != -1)
	{
		// if (sidedef.id == 4)
		// 	printf("are we here?\n");
		opp_sector = doom->lib.sector[sidedef.opp_sector];
		set_properties_plane_portal(doom, sidedef,\
			opp_sector, plane);
	}
	if (sector.action == 1)
		doom->lib.portal_ceiling = plane->sidedef_top;
}

void			set_properties_plane(t_doom *doom, t_sidedef sidedef,
					t_plane *plane, t_sector *sector)
{
	int x;

	x = plane->x;
	ft_bzero(plane, sizeof(plane));
	sidedef.distance *= cos(doom->ray_adjacent * x - FOV / 2);
	sidedef.prev_sidedef.distance *= \
		cos(doom->ray_adjacent * x - FOV / 2);
	*sector = doom->lib.sector[sidedef.sector];
	plane->intersect = sidedef.intersect;
	set_properties_plane_sidedef(doom, sidedef, *sector, plane);
	set_sector_properties(doom, sidedef, *sector, plane);
	set_floor_limit(doom, plane, sidedef, sector);
	// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
		// printf("plane_sidedef_bottom2: %d\n", plane->sidedef_bottom);
	set_ceiling_limit(doom, plane, sidedef, sector);
}

void			set_values_clipping_sprites(t_doom *doom, t_plane plane,\
				t_sidedef sidedef, int x)
{
	if (plane.sidedef_bottom >= 0 && plane.sidedef_bottom <= HEIGHT)
		doom->lib.sector[sidedef.sector].sidedef_bottom[x] = plane.sidedef_bottom;
	else
		doom->lib.sector[sidedef.sector].sidedef_bottom[x] = 0; //or set to -1
	if (plane.sidedef_top >= 0 && plane.sidedef_top <= HEIGHT)
		doom->lib.sector[sidedef.sector].sidedef_top[x] = plane.sidedef_top;
	else
		doom->lib.sector[sidedef.sector].sidedef_bottom[x] = 0; //or set to -1
	// if (plane.mid_texture_bottom >= 0 && plane.mid_texture_bottom <= HEIGHT)
	// 	doom->lib.sector[sidedef.sector].sidedef_top[x] = plane.mid_texture_bottom;
	// else
	// 	doom->lib.sector[sidedef.sector].sidedef_bottom[x] = 0; //or set to -1	
	
	if (sidedef.opp_sector != -1) //for clipping sprites (above two as well)
	{
		// if (doom->pos.x > 1952 && doom->pos.x < 2816 && doom->pos.y > 1255 && doom->pos.y < 1547)
			// printf("%d ", plane.mid_texture_bottom);
		
		doom->lib.sector[sidedef.sector].sidedef_mid_bottom[x] = plane.mid_texture_bottom;
	}	
	else
		doom->lib.sector[sidedef.sector].sidedef_mid_bottom[x] = 0; //or set to -1
}

void			project_on_plane(t_doom *doom, t_sidedef sidedef, int x)
{
	t_plane		plane;
	t_sector	sector;

	plane.x = x;
	set_properties_plane(doom, sidedef, &plane, &sector);
	//if (plane.sidedef_bottom == HEIGHT && plane.sidedef_top == 0)
	//	printf("%d\n", sidedef.id);
	if (sidedef.opp_sector == -1)
		draw_onesided_sidedef(doom, plane, sidedef, x);
	if (sidedef.action == 6)
		draw_window(doom, plane, sidedef, x);
	else
		draw_portal_sidedef(doom, plane, sidedef, x);
	if (sector.action != 1)
		draw_ceiling(doom, x, sector, plane.sidedef_top);
	draw_floor(doom, x, sector, plane.sidedef_bottom);
	set_values_clipping_sprites(doom, plane, sidedef, x);
	if (sidedef.poster != -1)
		draw_poster(doom, plane, sidedef.poster, x);
}

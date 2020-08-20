#include "../../includes/doom.h"

void		set_properties_plane_portal(t_doom *doom, t_sidedef sidedef,
					t_sector opp_sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			mid_top;
	int			mid_bottom;
	int			new_height;

	if (opp_sector.slope_floor_id != -1)
		set_slope_height(doom, sidedef, opp_sector);

	double diff = doom->texture_height - doom->player_height;
	
	new_height = (HEIGHT / 2);
	
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;
	
	double scale =  plane->height_standard / doom->texture_height;
	
	height_ceiling = opp_sector.height_ceiling / sidedef.distance * doom->dist_to_plane;

	mid_top = ((new_height) - (diff * scale)) - (doom->own_event.y_pitch - height_ceiling);

	height_floor = opp_sector.height_floor / sidedef.distance * doom->horizontal_plane_dist;
	
	mid_bottom = ((new_height) + (doom->player_height * scale)) - (doom->own_event.y_pitch - height_floor);

	// new_height = (HEIGHT / 2) + doom->player_height;// + (doom->up * 20);
	// // printf("portal new_height: %d\n", new_height);
	// // if (doom->own_event.scissor_lift_up == TRUE)
	// // 	new_height = (HEIGHT / 2) + (doom->up * 20);
	// // 	new_height += doom->up * 10;
	// height_ceiling = opp_sector.height_ceiling / \
	// 	sidedef.distance * doom->dist_to_plane;
	// mid_top = ((new_height - (plane->height_standard / 2)) - \
	// 	doom->own_event.y_pitch - height_ceiling);
	// plane->mid_texture_top = ((mid_top >= 0) ? mid_top : 0);
	// height_floor = opp_sector.height_floor / \
	// 	sidedef.distance * doom->dist_to_plane;
	// mid_bottom = ((new_height + (plane->height_standard / 2)) - \
	// 	doom->own_event.y_pitch - height_floor);
	// if (doom->own_event.scissor_lift_up == TRUE)
	// {
	// 	// printf("2\n");
	// 	mid_top += 30;
	// 	mid_bottom += 30;
	// 	// if (doom->own_event.y_pitch < 450)
	// 		// doom->own_event.y_pitch += 10;
	// 	// printf("1\n");./
	// }
	// if (doom->own_event.scissor_lift_down == TRUE)
	// {
	// 	mid_top -= 30;
	// 	mid_bottom -= 30;
	// 	wall_offset(plane, mid_top);
	// }
	if (mid_bottom < 0)
		mid_bottom = 0;
	if ( mid_top > HEIGHT)
		mid_top = HEIGHT;
	else if (mid_top < 0)
		mid_top = 0;
	plane->mid_texture_top = mid_top;
	plane->mid_texture_bottom = ((mid_bottom < HEIGHT) ? mid_bottom : (HEIGHT));
}

void		set_properties_plane_sidedef(t_doom *doom, t_sidedef sidedef,
					t_sector sector, t_plane *plane)
{
	double		height_floor;
	double		height_ceiling;
	int			sidedef_top;
	int			sidedef_bottom;
	int			new_height;
	int			diff;

	if (sector.slope_floor_id != -1)
		sector.height_floor += set_slope_height(doom, sidedef, sector);

	diff = doom->texture_height - doom->player_height;

	new_height = (HEIGHT / 2);
	plane->height_standard = doom->texture_height / sidedef.distance * doom->dist_to_plane;

	double scale =  plane->height_standard / doom->texture_height;

	height_ceiling = sector.height_ceiling / sidedef.distance * doom->dist_to_plane;

	sidedef_top = ((new_height) - (diff * scale)) - (doom->own_event.y_pitch - height_ceiling);

	height_floor = sector.height_floor / sidedef.distance * doom->horizontal_plane_dist;

	sidedef_bottom = ((new_height) + (doom->player_height * scale)) - (doom->own_event.y_pitch - height_floor);

	if (plane->sidedef_bottom < 0)
		plane->sidedef_bottom = 0;
	if (plane->sidedef_top > HEIGHT)
		plane->sidedef_top = HEIGHT;
	else if (plane->sidedef_top < 0)
		plane->sidedef_top = 0;
	wall_offset(plane, sidedef_top);
	plane->sidedef_bottom = \
		((sidedef_bottom < HEIGHT ? sidedef_bottom : (HEIGHT)));
}

#include "../../includes/doom.h"

// void	set_lines(t_sidedef *sidedef)
// {
// 	sidedef[0].id = 0;
// 	sidedef[0].line.start.x = 0;
// 	sidedef[0].line.start.y = 0;
// 	sidedef[0].line.end.x = 200;
// 	sidedef[0].line.end.y = 0;
// 	sidedef[0].sector = 0;
// 	sidedef[0].opp_sidedef = -1;
// 	sidedef[0].opp_sector = -1;

// 	sidedef[1].id = 1;
// 	sidedef[1].line.start.x = 200;
// 	sidedef[1].line.start.y = 0;
// 	sidedef[1].line.end.x = 200;
// 	sidedef[1].line.end.y = 250;
// 	sidedef[1].sector = 0;
// 	sidedef[1].opp_sidedef = 8;
// 	sidedef[1].opp_sector = 1;

// 	sidedef[2].id = 2;
// 	sidedef[2].line.start.x = 200;
// 	sidedef[2].line.start.y = 250;
// 	sidedef[2].line.end.x = 200;
// 	sidedef[2].line.end.y = 500;
// 	sidedef[2].sector = 0;
// 	sidedef[2].opp_sidedef = -1;
// 	sidedef[2].opp_sector = -1;
	
// 	sidedef[3].id = 3;
// 	sidedef[3].line.start.x = 200;
// 	sidedef[3].line.start.y = 500;
// 	sidedef[3].line.end.x = 0;
// 	sidedef[3].line.end.y = 500;
// 	sidedef[3].sector = 0;
// 	sidedef[3].opp_sidedef = -1;
// 	sidedef[3].opp_sector = -1;

// 	sidedef[4].id = 4;
// 	sidedef[4].line.start.x = 0;
// 	sidedef[4].line.start.y = 500;
// 	sidedef[4].line.end.x = 0;
// 	sidedef[4].line.end.y = 0;
// 	sidedef[4].sector = 0;
// 	sidedef[4].opp_sidedef = -1;
// 	sidedef[4].opp_sector = -1;
	
// 	sidedef[5].id = 5;
// 	sidedef[5].line.start.x = 200;
// 	sidedef[5].line.start.y = 0;
// 	sidedef[5].line.end.x = 300;
// 	sidedef[5].line.end.y = 0;
// 	sidedef[5].sector = 1;
// 	sidedef[5].opp_sidedef = -1;
// 	sidedef[5].opp_sector = -1;

// 	sidedef[6].id = 6;
// 	sidedef[6].line.start.x = 300;
// 	sidedef[6].line.start.y = 0;
// 	sidedef[6].line.end.x = 300;
// 	sidedef[6].line.end.y = 250;
// 	sidedef[6].sector = 1;
// 	sidedef[6].opp_sidedef = 12;
// 	sidedef[6].opp_sector = 2;

// 	sidedef[7].id = 7;
// 	sidedef[7].line.start.x = 300;
// 	sidedef[7].line.start.y = 250;
// 	sidedef[7].line.end.x = 200;
// 	sidedef[7].line.end.y = 250;
// 	sidedef[7].sector = 1;
// 	sidedef[7].opp_sidedef = -1;
// 	sidedef[7].opp_sector = -1;

// 	sidedef[8].id = 8;
// 	sidedef[8].line.start.x = 200;
// 	sidedef[8].line.start.y = 250;
// 	sidedef[8].line.end.x = 200;
// 	sidedef[8].line.end.y = 0;
// 	sidedef[8].sector = 1;
// 	sidedef[8].opp_sidedef = 1;
// 	sidedef[8].opp_sector = 0;

// 	sidedef[9].id = 9;
// 	sidedef[9].line.start.x = 300;
// 	sidedef[9].line.start.y = 0;
// 	sidedef[9].line.end.x = 500;
// 	sidedef[9].line.end.y = 0;
// 	sidedef[9].sector = 2;
// 	sidedef[9].opp_sidedef = -1;
// 	sidedef[9].opp_sector = -1;

// 	sidedef[10].id = 10;
// 	sidedef[10].line.start.x = 500;
// 	sidedef[10].line.start.y = 0;
// 	sidedef[10].line.end.x = 500;
// 	sidedef[10].line.end.y = 250;
// 	sidedef[10].sector = 2;
// 	sidedef[10].opp_sidedef = -1;
// 	sidedef[10].opp_sector = -1;

// 	sidedef[11].id = 11;
// 	sidedef[11].line.start.x = 500;
// 	sidedef[11].line.start.y = 250;
// 	sidedef[11].line.end.x = 300;
// 	sidedef[11].line.end.y = 250;
// 	sidedef[11].sector = 2;
// 	sidedef[11].opp_sidedef = -1;
// 	sidedef[11].opp_sector = -1;

// 	sidedef[12].id = 12;
// 	sidedef[12].line.start.x = 300;
// 	sidedef[12].line.start.y = 250;
// 	sidedef[12].line.end.x = 300;
// 	sidedef[12].line.end.y = 0;
// 	sidedef[12].sector = 2;
// 	sidedef[12].opp_sidedef = 6;
// 	sidedef[12].opp_sector = 1;
// }

void	doom_init_events(t_event *event)
{
	event->jump = FALSE;
	event->velocity = VELOCITY;
	event->floor_diff = 0;
	event->step_down = FALSE;
	event->jump = FALSE;
	event->y_pitch = 0;
}

void 	doom_init(t_doom *doom)
{
	if (sdl_init(doom) != 0)
		doom_exit_failure(doom, "unable to initialize SDL\n");
	doom->audio.engine = OFF;
	if (doom->audio.engine){
		init_audio(&doom->audio);
		load_audio(&doom->audio);
	}
	// set_lines(doom->sidedef);
	doom->is_running = TRUE;
	doom->light = TRUE;
	doom->hud = TRUE;
	doom->basket = FALSE;
	doom->shopping = FALSE;
	doom->dir_angle = 90;
	doom->ray_adjacent = FOV / WIDTH;
	doom->pos.x = 32;
	doom->pos.y = 130;
	doom->max_ray = 10000;
	doom->i_sector = 0;
	doom->player_height = 48;
	doom->visible_sprites = 0;
	doom->player_std_height = 48;
	doom->lib.sector[0].slope_id = 1;
	doom->lib.sector[0].slope_floor =  21.80140949 * (PI / 180);
	// doom->sector[0].height_ceiling = 64;
	// doom->sector[0].height_floor = 0;
	// doom->sector[0].i_sidedefs = 0;
	// doom->sector[0].n_sidedefs = 5;
	// doom->sector[0].slope_id = -1;
	// doom->sector[1].height_ceiling = 64;
	// doom->sector[1].height_floor = 20;
	// doom->sector[1].i_sidedefs = 5;
	// doom->sector[1].n_sidedefs = 4;
	// doom->sector[1].slope_id = 6;
	// doom->sector[1].slope_angle = 21.80140949 * (PI / 180); //tan-1(height floor hinging sector / lenght of floor) 
	//doom->sector[1].slope_id = -1;
	// doom->sector[2].height_ceiling = 64;
	// doom->sector[2].height_floor = 20;
	// doom->sector[2].i_sidedefs = 9;
	// doom->sector[2].n_sidedefs = 4;
	// doom->sector[2].slope_id = -1;
	doom->dist_to_plane = (WIDTH / 2) / tan(FOV / 2);
	doom_init_events(&doom->own_event);
}

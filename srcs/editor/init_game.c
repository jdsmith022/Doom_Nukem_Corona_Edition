#include "../../includes/doom.h"
#include "game_editor.h"

// void    add_walls(t_doom *doom)
// {
// 	int cur_sd;

//     add_sidedef(doom, 0 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
//     add_sidedef(doom, 96 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = 4;
//     add_sidedef(doom, 96 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
//     add_sidedef(doom, 96 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = 4;
//     add_sidedef(doom, 96 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = 7;
//     add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     // SIDEDEF[EDIT.cur_sd].txt_2 = 7;
//     SIDEDEF[EDIT.cur_sd].txt_2 = 7;
// 	SIDEDEF[EDIT.cur_sd].action = 2;
// 	SIDEDEF[EDIT.cur_sd].opp_sector = 1;
// 	SIDEDEF[EDIT.cur_sd].opp_sidedef = EDIT.w_len + 1;
// 	cur_sd = EDIT.cur_sd;
// 	// add_portal(doom, 1);
// 	EDIT.cur_sec = 1;
// 	add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = -1;
// 	SIDEDEF[EDIT.cur_sd].action = 2;
// 	SIDEDEF[EDIT.cur_sd].opp_sector = 0;
// 	SIDEDEF[EDIT.cur_sd].opp_sidedef = cur_sd;
// 	EDIT.cur_sec = 0;
//     add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     add_sidedef(doom, 0 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = 7;
//     add_sidedef(doom, 0 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
//     add_sidedef(doom, 0 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
//     SIDEDEF[EDIT.cur_sd].txt_2 = 0;
// }

// void    init_outside(t_doom *doom)
// {
// 	SECTOR[0].slope_floor = 0;
//     SECTOR[0].slope_floor_id = -1;
// 	SECTOR[0].slope_ceiling = 0;
// 	SECTOR[0].height_ceiling = 0;
// 	SECTOR[0].height_floor = 0;
// 	SECTOR[0].txt_floor = 1;
// 	SECTOR[0].txt_ceiling = 5;
// 	SECTOR[0].n_sidedefs = 0;
// 	SECTOR[0].i_sidedefs = 0;
// 	SECTOR[0].diff_x = 0;
// 	SECTOR[0].diff_y = 0;
// 	SECTOR[0].action = 1; 
// 	SECTOR[0].light_level = 10;
// 	SECTOR[0].id = 0;
// 	EDIT.portal_sec = -1;
//     // EDIT.pl_x= 32.0 + SECTOR[0].diff_x;
//     // EDIT.pl_y= 130.0 + SECTOR[0].diff_y;
// 	EDIT.pl_x = 32;
//     EDIT.pl_y = 130;
// 	add_sector(doom);
// 	SECTOR[1].diff_x = 0;
// 	SECTOR[1].diff_y = 0;
// 	EDIT.cur_sec = 0;
//     add_walls(doom);
// }

// void	init_game_design(t_doom *doom)
// {
// 	printf("%d\n", EDIT.sym_lib[plus]->h);
// 	SECTOR = (t_sector*)malloc(sizeof(t_sector) * 8);
// 	EDIT.s_size = 2;
// 	EDIT.s_len = 0;
// 	EDIT.cur_sec = 0;
// 	EDIT.cur_sd = -1;
// 	EDIT.pl_pos = 0;
// 	EDIT.pl_sec = 0;
// 	EDIT.w_len = 0;
// 	EDIT.s_len = 0;
//     init_outside(doom);
// 	EDIT.portal_sd = -1;
// 	// EDIT.w_len--;
// }

void	init_game_design(t_doom *doom)
{
	doom->game_design.sector = (t_sector*)malloc(sizeof(t_sector) * 2);
	doom->game_design.s_size = 2;
	doom->game_design.s_len = 0;
	doom->game_design.cur_sec = 0;
	doom->game_design.cur_sd = -1;
	doom->game_design.pl_pos = 0;
	doom->game_design.pl_sec = 0;
	doom->game_design.w_len = 0;
	doom->game_design.o_len = 0;
	doom->game_design.s_len = 0;
	doom->game_design.object_bar = 0;
	doom->game_design.sidedef_bar = 1;
	doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
		doom->game_design.sector[doom->game_design.s_len].slope_floor_id = -1;
	doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].i_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_y = 0;
	doom->game_design.sector[doom->game_design.s_len].action = 0;
	doom->game_design.sector[doom->game_design.s_len].light_level = 10;
	doom->game_design.portal_sec = -1;
	doom->game_design.portal_sd = -1;
}

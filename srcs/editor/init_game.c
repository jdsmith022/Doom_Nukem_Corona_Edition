#include "../../includes/doom.h"
#include "game_editor.h"

void    add_walls(t_doom *doom)
{
	int cur_sd;

    add_sidedef(doom, 0 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
    add_sidedef(doom, 96 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = 4;
    add_sidedef(doom, 96 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
    add_sidedef(doom, 96 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = 4;
    add_sidedef(doom, 96 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = 7;
    add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    // SIDEDEF[EDIT.cur_sd].txt_2 = 7;
    SIDEDEF[EDIT.cur_sd].txt_2 = -1;
	// SIDEDEF[EDIT.cur_sd].action = 2;
	SIDEDEF[EDIT.cur_sd].opp_sector = 1;
	SIDEDEF[EDIT.cur_sd].opp_sidedef = EDIT.w_len + 1;
	cur_sd = EDIT.cur_sd;
	EDIT.cur_sec = 1;
	add_sidedef(doom, 60 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = -1;
	// SIDEDEF[EDIT.cur_sd].action = 2;
	SIDEDEF[EDIT.cur_sd].opp_sector = 0;
	SIDEDEF[EDIT.cur_sd].opp_sidedef = cur_sd;
	EDIT.cur_sec = 0;
    add_sidedef(doom, 30 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    add_sidedef(doom, 0 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = 7;
    add_sidedef(doom, 0 + SECTOR[0].diff_x, 96 + SECTOR[0].diff_y);
    add_sidedef(doom, 0 + SECTOR[0].diff_x, 0 + SECTOR[0].diff_y);
    SIDEDEF[EDIT.cur_sd].txt_2 = 0;
}

void    init_outside(t_doom *doom)
{
	SECTOR[0].slope_floor = 0;
    SECTOR[0].slope_floor_id = -1;
	SECTOR[0].slope_ceiling = 0;
	SECTOR[0].height_ceiling = 0;
	SECTOR[0].height_floor = 0;
	SECTOR[0].txt_floor = 1;
	SECTOR[0].txt_ceiling = 5;
	SECTOR[0].n_sidedefs = 0;
	SECTOR[0].i_sidedefs = 0;
	SECTOR[0].diff_x = 352;
	SECTOR[0].diff_y = 252;
	// SECTOR[0].outside = 1; 
	SECTOR[0].outside = 0; 
	SECTOR[0].light_level = 10;
	SECTOR[0].id = 0;
	EDIT.portal_sec = -1;
    // EDIT.pl_x= 32.0 + SECTOR[0].diff_x;
    // EDIT.pl_y= 130.0 + SECTOR[0].diff_y;
	EDIT.pl_x = 400;
    EDIT.pl_y = 300;
	add_sector(doom);
	SECTOR[1].diff_x = 352;
	SECTOR[1].diff_y = 252;
	EDIT.cur_sec = 0;
    add_walls(doom);
}

void	init_inside(t_doom *doom)
{
	SECTOR[1].diff_x = 352;
	SECTOR[1].diff_y = 252;
}

void	init_game_design(t_doom *doom)
{
	printf("%d\n", EDIT.sym_lib[plus]->h);
	SECTOR = (t_sector*)malloc(sizeof(t_sector) * 2);
	EDIT.s_size = 2;
	EDIT.s_len = 0;
	EDIT.cur_sec = 0;
	EDIT.cur_sd = -1;
	EDIT.pl_pos = 0;
	EDIT.pl_sec = 0;
	EDIT.w_len = 0;
	EDIT.s_len = 0;
    init_outside(doom);
	init_inside(doom);
	EDIT.portal_sd = -1;
	// EDIT.w_len--;
}
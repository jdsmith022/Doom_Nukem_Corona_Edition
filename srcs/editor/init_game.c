#include "../../includes/doom.h"
#include "game_editor.h"

void    add_walls(t_doom *doom)
{
    add_sidedef(doom, 300, 200);
    add_sidedef(doom, 300, 296);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 4;
    add_sidedef(doom, 396, 200);
    add_sidedef(doom, 396, 296);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 4;
    add_sidedef(doom, 396, 296);
    add_sidedef(doom, 360, 296);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 7;
    add_sidedef(doom, 360, 296);
    add_sidedef(doom, 330, 296);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 7;
    add_sidedef(doom, 330, 296);
    add_sidedef(doom, 300, 296);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 7;
    add_sidedef(doom, 300, 296);
    add_sidedef(doom, 300, 200);
    doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 = 0;
}

void    init_outside(t_doom *doom)
{
	doom->game_design.sector[0].slope_floor = 0;
    doom->game_design.sector[0].slope_floor_id = -1;
	doom->game_design.sector[0].slope_ceiling = 0;
	doom->game_design.sector[0].height_ceiling = 0;
	doom->game_design.sector[0].height_floor = 0;
	doom->game_design.sector[0].txt_floor = 1;
	doom->game_design.sector[0].txt_ceiling = 5;
	doom->game_design.sector[0].n_sidedefs = 0;
	doom->game_design.sector[0].i_sidedefs = 0;
	doom->game_design.sector[0].diff_x = 300;
	doom->game_design.sector[0].diff_y = 200;
	doom->game_design.sector[0].outside = 1;
	doom->game_design.sector[0].light_level = 10;
	doom->game_design.sector[0].id = 0;
	doom->game_design.portal_sec = -1;
    doom->game_design.pl_x= 32;
    doom->game_design.pl_y= 130;
    add_walls(doom);
}

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
	doom->game_design.s_len = 0;
    init_outside(doom);
	doom->game_design.portal_sd = -1;
}
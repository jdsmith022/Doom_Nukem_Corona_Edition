#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

void			init_sidedef_textures(t_doom *doom)
{
	doom->game_design.sd_tex_index[0] = 15;
	doom->game_design.sd_tex_index[1] = 16;
	doom->game_design.sd_tex_index[2] = 20;
	doom->game_design.sd_tex_index[3] = 22;
	doom->game_design.sd_tex_index[4] = 27;
	doom->game_design.sd_tex_index[5] = 30;
	doom->game_design.sd_tex_index[6] = 37;
	doom->game_design.sd_tex_index[7] = 44;
	doom->game_design.sd_tex_index[8] = 66;
	doom->game_design.sd_tex_index[9] = 69;
	doom->game_design.sd_tex_index[10] = 71;
	doom->game_design.sd_tex_index[11] = 76;
}

void			init_game_design(t_doom *doom)
{
	doom->game_design.txt_1 = 0;
	doom->game_design.txt_3 = 1;
	doom->game_design.txt_ceiling = 1;
	doom->game_design.txt_floor = 0;
	doom->game_design.s_size = 2;
	doom->game_design.sd_len = 0;
	doom->game_design.sc_len = 0;
	doom->game_design.cur_sec = 0;
	doom->game_design.cur_sd = 0;
	doom->game_design.cur_tex = 0;
	doom->game_design.cur_obj = -1;
	doom->game_design.pl_pos = 0;
	doom->game_design.pl_sec = 0;
	doom->game_design.w_len = 0;
	doom->game_design.o_len = 0;
	doom->game_design.sc_len = 0;
	doom->game_design.object_bar = 0;
	doom->game_design.sidedef_bar = 1;
	doom->game_design.portal_sec = -1;
	doom->game_design.portal_sd = -1;
	doom->game_design.cur_tex = 7;
	doom->game_design.custom_level = TRUE;
	doom->game_design.draw_line.start.x = -1;
	doom->game_design.draw_line.end.x = -1;
	doom->game_design.ed_sector = ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector)
		doom_exit_failure(doom, "error: game design sector malloc");
	doom->game_design.sc_head = doom->game_design.ed_sector;
	doom->game_design.ed_sector->next = NULL;
	doom->game_design.ed_sector->light_level = 10;
	doom->game_design.ed_sector->height_ceiling = 0;
	doom->game_design.ed_sector->height_floor = 0;
	doom->game_design.ed_sidedef = ft_memalloc(sizeof(t_ed_sidedef));
	if (!doom->game_design.ed_sidedef)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	doom->game_design.sd_head = doom->game_design.ed_sidedef;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.player_placed = FALSE;
	init_sidedef_textures(doom);
}

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void		init_first_sector(t_doom *doom)
{
	doom->game_design.sector[doom->game_design.s_len].slope_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].slope_floor_id = -1;
	doom->game_design.sector[doom->game_design.s_len].slope_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].height_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_floor = 0;
	doom->game_design.sector[doom->game_design.s_len].txt_ceiling = 0;
	doom->game_design.sector[doom->game_design.s_len].n_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].i_sidedefs = 0;
	doom->game_design.sector[doom->game_design.s_len].n_objects = 0;
	doom->game_design.sector[doom->game_design.s_len].i_objects = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_x = 0;
	doom->game_design.sector[doom->game_design.s_len].diff_y = 0;
	doom->game_design.sector[doom->game_design.s_len].action = 0;
	doom->game_design.sector[doom->game_design.s_len].light_level = 10;
}

void			init_game_design(t_doom *doom)
{
	doom->game_design.sector = (t_sector*)malloc(sizeof(t_sector) * 2);
	if (doom->game_design.sector == NULL)
		doom_exit_failure(doom, "error: game design sector malloc");
	doom->game_design.txt_1 = 0;
	doom->game_design.txt_3 = 1;
	doom->game_design.txt_ceiling = 1;
	doom->game_design.txt_floor = 0;
	doom->game_design.s_size = 2;
	doom->game_design.s_len = 0;
	doom->game_design.cur_sec = 0;
	doom->game_design.cur_sd = -1;
	doom->game_design.cur_tex = 0;
	doom->game_design.cur_obj = -1;
	doom->game_design.pl_pos = 0;
	doom->game_design.pl_sec = 0;
	doom->game_design.w_len = 0;
	doom->game_design.o_len = 0;
	doom->game_design.s_len = 0;
	doom->game_design.object_bar = 0;
	doom->game_design.sidedef_bar = 1;
	doom->game_design.portal_sec = -1;
	doom->game_design.portal_sd = -1;
	doom->game_design.cur_tex = 7;
	doom->game_design.custom_level = TRUE;
	doom->game_design.draw_line.start.x = -1;
	doom->game_design.draw_line.end.x = -1;
	doom->game_design.ed_sidedef = ft_memalloc(sizeof(t_ed_sidedef) * 1);
	if (!doom->game_design.ed_sidedef)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	doom->game_design.ed_sidedef->next = NULL;
	init_first_sector(doom);
}

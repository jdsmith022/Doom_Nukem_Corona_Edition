#include "../../includes/doom.h"
#include "../../includes/game_editor.h"

static void			init_editor_sprites(t_doom *doom)
{
	doom->game_design.ed_spr_index[0] = SHOPPER;
	doom->game_design.ed_spr_index[1] = FACE_MASK;
	doom->game_design.ed_spr_index[2] = HEALTH_PACK_PLUS;
	doom->game_design.ed_spr_index[3] = HEALTH_PACK;
	doom->game_design.ed_spr_index[4] = CORONA;
	doom->game_design.ed_spr_index[5] = SPR_CHECKOUT;
}

static void			init_sidedef_textures(t_doom *doom)
{
	doom->game_design.sd_tex_index[0] = 15;
	doom->game_design.sd_tex_index[1] = 16;
	doom->game_design.sd_tex_index[2] = 19;
	doom->game_design.sd_tex_index[3] = 62;
	doom->game_design.sd_tex_index[4] = 28;
	doom->game_design.sd_tex_index[5] = 39;
	doom->game_design.sd_tex_index[6] = 64;
	doom->game_design.sd_tex_index[7] = 74;
	doom->game_design.sd_tex_index[8] = 75;
	doom->game_design.sd_tex_index[9] = 27;
	doom->game_design.sd_tex_index[10] = 34;
	doom->game_design.sd_tex_index[11] = 23;
}

static void			init_lists(t_doom *doom)
{
	doom->game_design.ed_sector = \
		(t_ed_sector*)ft_memalloc(sizeof(t_ed_sector));
	if (!doom->game_design.ed_sector)
		doom_exit_failure(doom, "error: game design sector malloc");
	doom->game_design.ed_sidedef = \
		(t_ed_sidedef*)ft_memalloc(sizeof(t_ed_sidedef));
	if (!doom->game_design.ed_sidedef)
		doom_exit_failure(doom, "error: malloc sidedef in editor\n");
	doom->game_design.ed_sprite = \
		(t_ed_sprite*)ft_memalloc(sizeof(t_ed_sprite));
	if (!doom->game_design.ed_sprite)
		doom_exit_failure(doom, "error: malloc sprite in editor\n");
	doom->game_design.sc_head = doom->game_design.ed_sector;
	doom->game_design.ed_sector->next = NULL;
	doom->game_design.ed_sector->light_level = 10;
	doom->game_design.ed_sector->height_ceiling = 0;
	doom->game_design.ed_sector->height_floor = 0;
	doom->game_design.sd_head = doom->game_design.ed_sidedef;
	doom->game_design.ed_sidedef->next = NULL;
	doom->game_design.ed_sprite->next = NULL;
	doom->game_design.sp_head = doom->game_design.ed_sprite;
	doom->game_design.sp_head->id = -1;
	doom->game_design.sp_head->sector = -1;
}

void				init_game_design(t_doom *doom)
{
	doom->game_design.sd_len = 0;
	doom->game_design.sc_len = 0;
	doom->game_design.tex_index = 0;
	doom->game_design.spr_len = 0;
	doom->game_design.spr_tex = 0;
	doom->game_design.pl_pos = 0;
	doom->game_design.sc_len = 0;
	doom->game_design.light_level = 10;
	doom->game_design.custom_level = TRUE;
	doom->game_design.draw_line.start.x = -1;
	doom->game_design.draw_line.end.x = -1;
	doom->game_design.place_checkout = FALSE;
	init_lists(doom);
	init_sidedef_textures(doom);
	init_editor_sprites(doom);
}

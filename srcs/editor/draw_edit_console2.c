#include "../../includes/doom.h"
#include "game_editor.h"
#include "sprites.h"
#include "../../includes/render.h"

void	draw_sector_images(Uint32 *pixels, t_doom *doom)
{
	int state;

	state = doom->game_design.sidedef_bar;
	doom->game_design.sidedef_bar = 1;
	put_images(DEL_SECTOR_X, DEL_SECTOR_Y, garbage, doom);
	put_images(ADD_SECTOR_X, ADD_SECTOR_Y, plus, doom);
	put_images(AR_LEFT_X, AR_LEFT_Y, arrow_left, doom);
	put_images(AR_RIGHT_X, AR_RIGHT_Y, arrow_right, doom);
	put_textures(TEX_FL_X, TEX_FL_Y, \
	doom->game_design.sector[doom->game_design.cur_sec].txt_floor, doom);
	put_images(AR_LEFT_TF_X, AR_LEFT_TF_Y, arrow_left, doom);
	put_images(AR_RIGHT_TF_X, AR_RIGHT_TF_Y, arrow_right, doom);
	put_textures(TEX_CE_X, TEX_CE_Y, \
	doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling, doom);
	put_images(AR_LEFT_TC_X, AR_LEFT_TC_Y, arrow_left, doom);
	put_images(AR_RIGHT_TC_X, AR_RIGHT_TC_Y, arrow_right, doom);
	doom->game_design.sidedef_bar = state;
}

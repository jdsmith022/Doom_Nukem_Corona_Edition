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

void	draw_sidedef_textures(Uint32 *pixels, t_doom *doom)
{
	if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 != -1)
		put_textures(TEX_S2_X, TEX_S2_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_2, doom);
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef != -1)
	{
		if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_1 != -1)
			put_textures(TEX_S1_X, TEX_S1_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_1, doom);
		put_images(AR_LEFT_TS1_X, AR_LEFT_TS1_Y, arrow_left, doom);
		put_images(AR_RIGHT_TS1_X, AR_RIGHT_TS1_Y, arrow_right, doom);
		if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_3 != -1)
			put_textures(TEX_S3_X, TEX_S3_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_3, doom);
		put_images(AR_LEFT_TS3_X, AR_LEFT_TS3_Y, arrow_left, doom);
		put_images(AR_RIGHT_TS3_X, AR_RIGHT_TS3_Y, arrow_right, doom);
	}
}

void	draw_sidedef_images(Uint32 *pixels, t_doom *doom)
{
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
	if (doom->game_design.cur_sd >= \
	doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs \
	&& doom->game_design.sidedef_bar == 1)
	{
		put_images(RM_SD_X, RM_SD_Y, garbage, doom);
		put_images(PORTAL_X, PORTAL_Y, plus, doom);
		draw_sidedef_textures(pixels, doom);
	}
	if (doom->game_design.portal_sec != -1)
	{
		put_images(AR_LEFT_SC_X, AR_LEFT_SC_Y, arrow_left, doom);
		put_images(AR_RIGHT_SC_X, AR_RIGHT_SC_Y, arrow_right, doom);
	}
}

void	draw_object_images(Uint32 *pixels, t_doom *doom)
{
	SDL_Rect texture;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_S2_X;
	texture.y = TEX_S2_Y;
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
	draw_img(doom->lib.obj_lib[doom->game_design.cur_obj], doom, texture);
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	if (doom->game_design.cur_obj >= \
	doom->game_design.sector[doom->game_design.cur_sec].i_objects \
	&& doom->game_design.object_bar == 1)
		put_images(DEL_OBJ_X, DEL_OBJ_Y, garbage, doom);
}

void	draw_map_images(Uint32 *pixels, t_doom *doom)
{
	put_images(AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left, doom);
	put_images(AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right, doom);
	put_images(AR_UP_M_X, AR_UP_M_Y, arrow_down, doom);
	put_images(AR_DOWN_M_X, AR_DOWN_M_Y, arrow_up, doom);
}

void    draw_images(Uint32 *pixels, t_doom *doom)
{
	draw_sector_images(pixels, doom);
	draw_map_images(pixels, doom);
	if (doom->game_design.sidedef_bar == 1)
		draw_sidedef_images(pixels, doom);
	if (doom->game_design.object_bar == 1)
		draw_object_images(pixels, doom);
	put_images(SIDEDEF_BUTTON_X, SIDEDEF_BUTTON_Y, plus, doom);
	put_images(SECTOR_BUTTON_X, SECTOR_BUTTON_Y, plus, doom);
}
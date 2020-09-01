#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

static void		draw_sidedef_textures(Uint32 *pixels, t_doom *doom)
{
	put_textures(TEX_S2_X, TEX_S2_Y, \
		doom->game_design.cur_tex, doom);
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
}

static void		draw_sidedef_images(Uint32 *pixels, t_doom *doom)
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

static void		draw_object_images(Uint32 *pixels, t_doom *doom)
{
	SDL_Rect texture;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_S2_X;
	texture.y = TEX_S2_Y;
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
	draw_img(doom->lib.obj_lib[doom->game_design.cur_tex], doom, texture);
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	if (doom->game_design.cur_obj >= \
	doom->game_design.sector[doom->game_design.cur_sec].i_objects \
	&& doom->game_design.object_bar == 1)
		put_images(DEL_OBJ_X, DEL_OBJ_Y, garbage, doom);
}

static void		draw_map_images(Uint32 *pixels, t_doom *doom)
{
	put_images(AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left, doom);
	put_images(AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right, doom);
	put_images(AR_UP_M_X, AR_UP_M_Y, arrow_down, doom);
	put_images(AR_DOWN_M_X, AR_DOWN_M_Y, arrow_up, doom);
}

void			draw_images(Uint32 *pixels, t_doom *doom)
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

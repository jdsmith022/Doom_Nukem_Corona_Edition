#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"

static void		place_checkout_sprite(t_doom *doom)
{
		SDL_Rect texture;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_SPR_X;
	texture.y = TEX_SPR_Y;
	draw_img(doom->lib.obj_lib[SPR_CHECKOUT], doom, texture);
}

static void		draw_object_images(Uint32 *pixels, t_doom *doom)
{
	SDL_Rect texture;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_S2_X;
	texture.y = TEX_S2_Y;
	// if (doom->game_design.place_checkout == TRUE)
	// 	place_checkout_sprite(doom);
	// else
	// {
		put_images(CROSS_P_X, CROSS_P_Y, player, doom);
		put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
		put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
		draw_img(doom->lib.obj_lib[doom->game_design.tex_index], doom, texture);
		put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
		put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
		put_images(DEL_OBJ_X, DEL_OBJ_Y, garbage, doom);
	// }
}

static void		draw_map_images(Uint32 *pixels, t_doom *doom)
{
	put_images(AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left, doom);
	put_images(AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right, doom);
	put_images(AR_UP_M_X, AR_UP_M_Y, arrow_down, doom);
	put_images(AR_DOWN_M_X, AR_DOWN_M_Y, arrow_up, doom);
}

static void		draw_edit_images(t_doom *doom, Uint32 *pixels,
					int index, SDL_Rect texture)
{
	bars(&pixels, doom);
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
	put_images(RM_SD_X, RM_SC_Y, garbage, doom);
	put_images(DEL_SECTOR_X, DEL_SECTOR_Y, garbage, doom);
	put_images(PORTAL_X, PORTAL_Y, plus, doom);
	put_images(AR_LEFT_X, AR_LEFT_Y, arrow_left, doom);
	put_images(AR_RIGHT_X, AR_LEFT_Y, arrow_right, doom);
	draw_img(doom->lib.obj_lib[index], doom, texture);
}

void			draw_images(Uint32 *pixels, t_doom *doom)
{
	SDL_Rect texture;
	int		index;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_SPR_X;
	texture.y = TEX_SPR_Y;
	index = doom->game_design.ed_spr_index[doom->game_design.spr_tex];
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	put_textures_sidedef(TEX_S2_X, TEX_S2_Y, \
	doom->game_design.tex_index, doom);
	put_images(RM_SD_X, RM_SD_Y, garbage, doom);
	if (doom->game_design.object_bar == 1 || \
	doom->game_design.place_checkout == TRUE)
		draw_object_images(pixels, doom);
	else if (doom->game_design.player_placed == TRUE)
		put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	else if (doom->game_design.edit_sector == TRUE)
		draw_edit_images(doom, pixels, index, texture);
	draw_map_images(pixels, doom);
}

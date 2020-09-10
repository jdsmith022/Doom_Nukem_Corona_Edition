/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_edit_console.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/10 13:50:00 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/render.h"

static void		draw_sector_images(t_doom *doom, Uint32 *pixels)
{
	SDL_Rect	texture;
	int			index;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_SPR_X;
	texture.y = TEX_SPR_Y;
	index = doom->game_design.i_spr_tex;
	bars(&pixels, doom);
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);
	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);
	put_images(RM_SD_X, RM_SC_Y, garbage, doom);
	put_images(AR_LEFT_X, AR_LEFT_Y, arrow_left, doom);
	put_images(AR_RIGHT_X, AR_LEFT_Y, arrow_right, doom);
	draw_img(doom->lib.obj_lib[index], doom, texture);
}

static void		draw_sidedef_images(t_doom *doom)
{
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	put_textures_sidedef(TEX_S2_X, TEX_S2_Y, \
	doom->game_design.i_sd_tex, doom);
}

void			draw_images(Uint32 *pixels, t_doom *doom)
{
	draw_sidedef_images(doom);
	draw_sector_images(doom, pixels);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_edit_console.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/31 17:45:33 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 12:57:50 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/game_editor.h"
#include "../../includes/sprites.h"
#include "../../includes/render.h"
#include "../../includes/font.h"

static void		place_checkout_sprite(t_doom *doom)
{
	TTF_Font	*font;
	t_font		lib;
	SDL_Rect	texture;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_SPR_X;
	texture.y = TEX_SPR_Y;
	draw_img(doom->lib.obj_lib[SPR_CHECKOUT], doom, texture);
	font = doom->lib.font_lib.font_18;
	lib.str = "Place checkout";
	lib.font_color = doom->lib.font_lib.font_color.black;
	lib.font_rect.x = 24;
	lib.font_rect.y = 480;
	single_font_to_sdl(doom, lib, font);
}

static void		draw_sector_images(t_doom *doom, Uint32 *pixels)
{
	SDL_Rect	texture;
	int			index;

	texture.h = 8;
	texture.w = 8;
	texture.x = TEX_SPR_X;
	texture.y = TEX_SPR_Y;
	index = doom->game_design.ed_spr_index[doom->game_design.spr_tex];
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

static void		draw_sidedef_images(t_doom *doom)
{
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);
	put_textures_sidedef(TEX_S2_X, TEX_S2_Y, \
	doom->game_design.tex_index, doom);
	put_images(RM_SD_X, RM_SD_Y, garbage, doom);
}

void			draw_images(Uint32 *pixels, t_doom *doom)
{
	if (doom->game_design.place_checkout == FALSE)
		draw_sidedef_images(doom);
	if (doom->game_design.edit_sector == TRUE && \
	doom->game_design.place_checkout == FALSE)
		draw_sector_images(doom, pixels);
}

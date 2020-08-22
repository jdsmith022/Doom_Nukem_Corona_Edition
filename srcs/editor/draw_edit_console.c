#include "../../includes/doom.h"
#include "game_editor.h"
#include "sprites.h"

void put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
				Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;

	pixels = doom->surface->pixels;
	texture = EDIT.sym_lib[tex_dex]->pixels;
	pixels[index] =  texture[pixel_dex];
	pixels[index + 1] = texture[pixel_dex + 1];
	pixels[index + 2] = texture[pixel_dex + 2];
}

void    put_textures(int x, int y, int index, t_doom *doom)
{
    int save_x;
	Uint32 shift;
    double sx;
	double sy;
	double change_x;
	double change_y;
	SDL_Surface		*texture;


    save_x = x;
    sx = 0;
	sy = 0;
	texture = EDIT.sidedef_bar == 1 ? doom->lib.tex_lib[index] : doom->lib.obj_lib[index];
	shift = texture->format->BitsPerPixel == 24 ? 3 : 4;
	change_x = (double)texture->w / 48.0;
	change_y = (double)texture->h / 48.0;
    while ((int)sy < texture->h)
    {
		put_texture(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4), (Uint32)(((int)sy * texture->w + (int)sx) * shift));
		x++;
		sx += change_x;
        if ((int)sx >= texture->w)
        {
            x = save_x;
            y++;
			sx = 0;
			sy += change_y;
        }
    }
}

void	put_images(int x, int y, int index, t_doom *doom)
{
    int save_x;
	Uint32 shift;
    double sx;
	double sy;
	double change_x;
	double change_y;

    save_x = x;
    sx = 0;
	sy = 0;
	shift = EDIT.sym_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
	change_x = (double)EDIT.sym_lib[index]->w / 32.0;
	change_y = (double)EDIT.sym_lib[index]->h / 32.0;
    while ((int)sy < EDIT.sym_lib[index]->h)
    {
		put_symbol(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4), (Uint32)(((int)sy * EDIT.sym_lib[index]->w + (int)sx) * shift));
		x++;
		sx += change_x;
        if ((int)sx >= EDIT.sym_lib[index]->w)
        {
            x = save_x;
            y++;
			sx = 0;
			sy += change_y;
        }
    }
}

void    draw_screen_colors(Uint32 *pixels, t_doom *doom)
{
    int x;
    int y;

    y = 0;
    while (y < HEIGHT)
	{
        x = 0;
		while (x < WIDTH)
		{
			if (x < WIDTH - (WIDTH / 5) && x > WIDTH / 5)
					pixels[((y * WIDTH) + x)] = 0;
			else
				pixels[((y * WIDTH) + x)] = 0x8c3cde6;
            x++;
		}
        y++;
	}
}

void	draw_sector_images(Uint32 *pixels, t_doom *doom)
{
	int state;

	state = EDIT.sidedef_bar;
	EDIT.sidedef_bar = 1;
	put_images(DEL_SECTOR_X, DEL_SECTOR_Y, garbage, doom);
	put_images(ADD_SECTOR_X, ADD_SECTOR_Y, plus, doom);

	put_images(AR_LEFT_X, AR_LEFT_Y, arrow_left, doom);
	put_images(AR_RIGHT_X, AR_RIGHT_Y, arrow_right, doom);

	put_textures(TEX_FL_X, TEX_FL_Y, SECTOR[EDIT.cur_sec].txt_floor, doom);
	put_images(AR_LEFT_TF_X, AR_LEFT_TF_Y, arrow_left, doom);
	put_images(AR_RIGHT_TF_X, AR_RIGHT_TF_Y, arrow_right, doom);

	put_textures(TEX_CE_X, TEX_CE_Y, SECTOR[EDIT.cur_sec].txt_ceiling, doom);
	put_images(AR_LEFT_TC_X, AR_LEFT_TC_Y, arrow_left, doom);
	put_images(AR_RIGHT_TC_X, AR_RIGHT_TC_Y, arrow_right, doom);
	EDIT.sidedef_bar = state;
}

void	draw_sidedef_images(Uint32 *pixels, t_doom *doom)
{
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);

	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);

	if (EDIT.cur_sd >= SECTOR[EDIT.cur_sec].i_sidedefs && EDIT.sidedef_bar == 1)
	{
		put_images(RM_SD_X, RM_SD_Y, garbage, doom);
		put_images(PORTAL_X, PORTAL_Y, plus, doom);

		if (SIDEDEF[EDIT.cur_sd].txt_2 != -1)
			put_textures(TEX_S2_X, TEX_S2_Y, SIDEDEF[EDIT.cur_sd].txt_2, doom);
		put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
		put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);

		if (SIDEDEF[EDIT.cur_sd].opp_sidedef != -1)
		{
			if (SIDEDEF[EDIT.cur_sd].txt_1 != -1)
				put_textures(TEX_S1_X, TEX_S1_Y, SIDEDEF[EDIT.cur_sd].txt_1, doom);
			put_images(AR_LEFT_TS1_X, AR_LEFT_TS1_Y, arrow_left, doom);
			put_images(AR_RIGHT_TS1_X, AR_RIGHT_TS1_Y, arrow_right, doom);

			if (SIDEDEF[EDIT.cur_sd].txt_3 != -1)
				put_textures(TEX_S3_X, TEX_S3_Y, SIDEDEF[EDIT.cur_sd].txt_3, doom);
			put_images(AR_LEFT_TS3_X, AR_LEFT_TS3_Y, arrow_left, doom);
			put_images(AR_RIGHT_TS3_X, AR_RIGHT_TS3_Y, arrow_right, doom);
		}
	}
	if (EDIT.portal_sec != -1)
	{
		put_images(AR_LEFT_SC_X, AR_LEFT_SC_Y, arrow_left, doom);
		put_images(AR_RIGHT_SC_X, AR_RIGHT_SC_Y, arrow_right, doom);
	}
}

void	draw_object_images(Uint32 *pixels, t_doom *doom)
{
	put_images(CROSS_P_X, CROSS_P_Y, player, doom);

	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);

	put_textures(TEX_S2_X, TEX_S2_Y, LEVEL_SPRITES[EDIT.cur_tex].tex1, doom);
	put_images(AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left, doom);
	put_images(AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right, doom);

	if (EDIT.cur_obj >= SECTOR[EDIT.cur_sec].i_objects && EDIT.object_bar == 1)
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
	if (EDIT.sidedef_bar == 1)
		draw_sidedef_images(pixels, doom);
	if (EDIT.object_bar == 1)
		draw_object_images(pixels, doom);
	put_images(SIDEDEF_BUTTON_X, SIDEDEF_BUTTON_Y, plus, doom);
	put_images(SECTOR_BUTTON_X, SECTOR_BUTTON_Y, plus, doom);
}
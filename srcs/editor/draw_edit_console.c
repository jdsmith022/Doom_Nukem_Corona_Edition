#include "../../includes/doom.h"
#include "game_editor.h"


void    put_textures(int x, int y, int index, t_doom *doom)
{
	char *tex;
	char *pix;
    int save_x;
	Uint32 shift;
    int sx;

    save_x = x;
    sx = 0;
	shift = doom->lib.tex_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
    while (sx < (doom->lib.tex_lib[index]->h * doom->lib.tex_lib[index]->w))
    {
		put_texture(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4), (Uint32)(sx * shift));
		x++;
		sx++;
        if (sx % (doom->lib.tex_lib[index]->w) == 0)
        {
            x = save_x;
            y++;
        }
    }
}

void	put_images(Uint32 **pixels, int x, int y, int img)
{
	int save_x;
	int sx;

	save_x = x;
	sx = 0;
	while (sx < FRAME_WIDTH * FRAME_HEIGHT)
	{
		pixels[0][((y * WIDTH) + x)] = editor_sprites[img][sx];
		sx++;
		x++;
		if (sx % FRAME_WIDTH == 0)
		{
			x = save_x;
			y++;
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
			{
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == 0)
					pixels[((y * WIDTH) + x)] = 0;
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == -45)
					pixels[((y * WIDTH) + x)] = 0xff6e2020;
				if (doom->game_design.sector[doom->game_design.cur_sec].slope_floor == 45)
					pixels[((y * WIDTH) + x)] = 0xff065535;
			}
			else
				pixels[((y * WIDTH) + x)] = 0x8c3cde6;
            x++;
		}
        y++;
	}
}

void    draw_images(Uint32 *pixels, t_doom *doom)
{
	put_images(&pixels, MINUS_X, MINUS_Y, minus);
	put_images(&pixels, PLUS_X, PLUS_Y, plus);

	put_images(&pixels, D_45_X, D_45_Y, d_45);
	put_images(&pixels, STRAIGHT_X, STRAIGHT_Y, straight);
	put_images(&pixels, D_M45_X, D_M45_Y, d_m45);

	put_images(&pixels, AR_LEFT_X, AR_LEFT_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_X, AR_RIGHT_Y, arrow_right);

	put_images(&pixels, AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right);

	put_images(&pixels, AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right);
	put_images(&pixels, AR_UP_M_X, AR_UP_M_Y, arrow_left);
	put_images(&pixels, AR_DOWN_M_X, AR_DOWN_M_Y, arrow_right);

	put_images(&pixels, CROSS_X, CROSS_Y, cross);
	put_images(&pixels, CROSS_P_X, CROSS_P_Y, cross);

	put_textures(TEX_FL_X, TEX_FL_Y, doom->game_design.sector[doom->game_design.cur_sec].txt_floor, doom);
	put_images(&pixels, AR_LEFT_TF_X, AR_LEFT_TF_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_TF_X, AR_RIGHT_TF_Y, arrow_right);

	put_textures(TEX_CE_X, TEX_CE_Y, doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling, doom);
	put_images(&pixels, AR_LEFT_TC_X, AR_LEFT_TC_Y, arrow_left);
	put_images(&pixels, AR_RIGHT_TC_X, AR_RIGHT_TC_Y, arrow_right);

	if (doom->game_design.cur_sd >= doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs)
	{
		put_images(&pixels, PORTAL_X, PORTAL_Y, minus);
		put_images(&pixels, WALL_X, WALL_Y, plus);

		if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_2 != -1)
			put_textures(TEX_S2_X, TEX_S2_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_2, doom);
		put_images(&pixels, AR_LEFT_TS2_X, AR_LEFT_TS2_Y, arrow_left);
		put_images(&pixels, AR_RIGHT_TS2_X, AR_RIGHT_TS2_Y, arrow_right);

		if (doom->game_design.sidedef[doom->game_design.cur_sd].opp_sidedef != -1)
		{
			if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_1 != -1)
				put_textures(TEX_S1_X, TEX_S1_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_1, doom);
			put_images(&pixels, AR_LEFT_TS1_X, AR_LEFT_TS1_Y, arrow_left);
			put_images(&pixels, AR_RIGHT_TS1_X, AR_RIGHT_TS1_Y, arrow_right);

			if (doom->game_design.sidedef[doom->game_design.cur_sd].txt_3 != -1)
				put_textures(TEX_S3_X, TEX_S3_Y, doom->game_design.sidedef[doom->game_design.cur_sd].txt_3, doom);
			put_images(&pixels, AR_LEFT_TS3_X, AR_LEFT_TS3_Y, arrow_left);
			put_images(&pixels, AR_RIGHT_TS3_X, AR_RIGHT_TS3_Y, arrow_right);
		}
	}
	if (doom->game_design.portal_sec != -1)
	{
		put_images(&pixels, AR_LEFT_SC_X, AR_LEFT_SC_Y, arrow_left);
		put_images(&pixels, AR_RIGHT_SC_X, AR_RIGHT_SC_Y, arrow_right);
	}
}
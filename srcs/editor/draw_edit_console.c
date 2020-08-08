#include "../../includes/doom.h"
#include "game_editor.h"

void put_symbol(t_doom *doom, Uint32 tex_dex, Uint32 index,
				Uint32 pixel_dex)
{
	char	*pixels;
	char	*texture;

	pixels = doom->surface->pixels;
	texture = doom->game_design.sym_lib[tex_dex]->pixels;
	pixels[index] =  texture[pixel_dex];
	pixels[index + 1] = texture[pixel_dex + 1];
	pixels[index + 2] = texture[pixel_dex + 2];
}

void    put_textures(int x, int y, int index, t_doom *doom)
{
	// char *tex;
	// char *pix;
    int save_x;
	Uint32 shift;
    double sx;
	double sy;
	double change_x;
	double change_y;

    save_x = x;
    sx = 0;
	sy = 0;
	shift = doom->lib.tex_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
	change_x = (double)doom->lib.tex_lib[index]->w / 48.0;
	change_y = (double)doom->lib.tex_lib[index]->h / 48.0;
	// change_x = 1.0;
	// change_y = 1.0;
    while ((int)sy < (doom->lib.tex_lib[index]->h))
    {
		put_texture(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4), (Uint32)(((int)sy * doom->lib.tex_lib[index]->w + (int)sx) * shift));
		x++;
		sx += change_x;
        if ((int)sx >= doom->lib.tex_lib[index]->w)
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
	shift = doom->game_design.sym_lib[index]->format->BitsPerPixel == 24 ? 3 : 4;
	change_x = (double)doom->game_design.sym_lib[index]->w / 32.0;
	change_y = (double)doom->game_design.sym_lib[index]->h / 32.0;
    while ((int)sy < (doom->lib.tex_lib[index]->h) / 3)
    {
		put_symbol(doom, (Uint32)index, (Uint32)((y * WIDTH + x) * 4), (Uint32)(((int)sy * doom->game_design.sym_lib[index]->w + (int)sx) * shift));
		x++;
		sx += change_x;
        if ((int)sx >= doom->game_design.sym_lib[index]->w)
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
	// //put_images(MINUS_X, MINUS_Y, minus);
	put_images(PLUS_X, PLUS_Y, plus, doom);

	put_images(AR_LEFT_X, AR_LEFT_Y, arrow_left, doom);
	put_images(AR_RIGHT_X, AR_RIGHT_Y, arrow_right, doom);

	put_images(AR_LEFT_S_X, AR_LEFT_S_Y, arrow_left, doom);
	put_images(AR_RIGHT_S_X, AR_RIGHT_S_Y, arrow_right, doom);

	put_images(AR_LEFT_M_X, AR_LEFT_M_Y, arrow_left, doom);
	put_images(AR_RIGHT_M_X, AR_RIGHT_M_Y, arrow_right, doom);
	put_images(AR_UP_M_X, AR_UP_M_Y, arrow_up, doom);
	put_images(AR_DOWN_M_X, AR_DOWN_M_Y, arrow_down, doom);

	// put_images(CROSS_X, CROSS_Y, garbage, doom);
	//put_images(CROSS_P_X, CROSS_P_Y, garbage, doom);

	put_textures(TEX_FL_X, TEX_FL_Y, doom->game_design.sector[doom->game_design.cur_sec].txt_floor, doom);
	put_images(AR_LEFT_TF_X, AR_LEFT_TF_Y, arrow_left, doom);
	put_images(AR_RIGHT_TF_X, AR_RIGHT_TF_Y, arrow_right, doom);

	put_textures(TEX_CE_X, TEX_CE_Y, doom->game_design.sector[doom->game_design.cur_sec].txt_ceiling, doom);
	put_images(AR_LEFT_TC_X, AR_LEFT_TC_Y, arrow_left, doom);
	put_images(AR_RIGHT_TC_X, AR_RIGHT_TC_Y, arrow_right, doom);

	if (doom->game_design.cur_sd >= doom->game_design.sector[doom->game_design.cur_sec].i_sidedefs)
	{
		put_images(PORTAL_X, PORTAL_Y, plus, doom);
		put_images(WALL_X, WALL_Y, garbage, doom);

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
	if (doom->game_design.portal_sec != -1)
	{
		put_images(AR_LEFT_SC_X, AR_LEFT_SC_Y, arrow_left, doom);
		put_images(AR_RIGHT_SC_X, AR_RIGHT_SC_Y, arrow_right, doom);
	}
}
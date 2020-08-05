#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text2(t_doom *doom, t_font *lib)
{
	lib[4].font_rect.x = WIDTH / 20;
	lib[4].font_rect.y = 275;
	lib[4].font_color = doom->lib.font_lib.font_color.black;
	lib[5].str = "To shoot sanitizer, press E to active shoot mode.";
	lib[5].font_rect.x = WIDTH / 20;
	lib[5].font_rect.y = 350;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "Press left mouse key to fire. Press E to release shoot mode.";
	lib[6].font_rect.x = WIDTH / 20;
	lib[6].font_rect.y = 400;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "To initialize game editor, press M, B to save level, \
		N to exit level editor.";
	lib[7].font_rect.x = WIDTH / 20;
	lib[7].font_rect.y = 475;
	lib[7].font_color = doom->lib.font_lib.font_color.black;
	lib[8].str = "Back to menu";
	lib[8].font_rect.x = WIDTH / 2.41;
	lib[8].font_rect.y = 550;
	lib[8].font_color = doom->lib.font_lib.font_color.black;
}

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Movement: Press W to move foward, S to move backwards,";
	lib[0].font_rect.x = WIDTH / 20;
	lib[0].font_rect.y = 25;
	lib[0].font_color = doom->lib.font_lib.font_color.black;
	lib[1].str = "A to move left, D to move right.";
	lib[1].font_rect.x = WIDTH / 20;
	lib[1].font_rect.y = 75;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "To jump, press the Spacebar. To bend, press the X key.";
	lib[2].font_rect.x = WIDTH / 20;
	lib[2].font_rect.y = 150;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
	lib[3].str = "To select an item, such as a grocery, press Q to active \
		select mode.";
	lib[3].font_rect.x = WIDTH / 20;
	lib[3].font_rect.y = 225;
	lib[3].font_color = doom->lib.font_lib.font_color.black;
	lib[4].str = "Press left mouse key to select. Press Q again \
		to release mouse select mode.";
	set_text2(doom, lib);
}

void	save_setting_window_font(t_doom *doom, int *len)
{
	char		*font_path;
	int			font_size;

	*len = 9;
	doom->lib.font_lib.setting_menu_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.setting_menu_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.setting_menu_font, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 20;
	font_to_sdl(doom, doom->lib.font_lib.setting_menu_font, \
		font_path, font_size);
}

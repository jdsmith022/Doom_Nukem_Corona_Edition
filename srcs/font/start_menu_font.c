#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Doomed: Corona Edition";
	lib[0].font_rect.x = WIDTH / 3.5;
	lib[0].font_rect.y = 100;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
	lib[1].str = "Select an option:";
	lib[1].font_rect.x = WIDTH / 2.75;
	lib[1].font_rect.y = 200;
	lib[1].font_color = doom->lib.font_lib.font_color.green;
	lib[2].str = "Start Game";
	lib[2].font_rect.x = WIDTH / 2.42;
	lib[2].font_rect.y = 275;
	lib[2].font_color = doom->lib.font_lib.font_color.green;
	lib[3].str = "Settings";
	lib[3].font_rect.x = WIDTH / 2.27;
	lib[3].font_rect.y = 350;
	lib[3].font_color = doom->lib.font_lib.font_color.green;
	lib[4].str = "Game Editor";
	lib[4].font_rect.x = WIDTH / 2.41;
	lib[4].font_rect.y = 425;
	lib[4].font_color = doom->lib.font_lib.font_color.green;
}

void	save_start_menu_font(t_doom *doom, int *len)
{
	char		*font_path;
	int			font_size;

	*len = 5;
	doom->lib.font_lib.start_menu_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.start_menu_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.start_menu_font, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 30;
	font_to_sdl(doom, doom->lib.font_lib.start_menu_font, font_path, font_size);
}

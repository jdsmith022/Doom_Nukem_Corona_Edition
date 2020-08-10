#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Game Paused";
	lib[0].font_rect.x = WIDTH / 2.65;
	lib[0].font_rect.y = HEIGHT / 4;
	lib[0].font_color = doom->lib.font_lib.font_color.red;
	lib[1].str = "Continue";
	lib[1].font_rect.x = WIDTH / 2.35;
	lib[1].font_rect.y = HEIGHT / 2;
	lib[1].font_color = doom->lib.font_lib.font_color.green;
	lib[2].str = "Press ESC to exit";
	lib[2].font_rect.x = WIDTH / 2.7;
	lib[2].font_rect.y = HEIGHT - 100;
	lib[2].font_color = doom->lib.font_lib.font_color.red;
}

void	save_pause_font(t_doom *doom, int *len)
{
	char		*font_path;
	int			font_size;

	*len = 3;
	doom->lib.font_lib.pause_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.pause_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.pause_font, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 30;
	font_to_sdl(doom, doom->lib.font_lib.pause_font, font_path, font_size);
}
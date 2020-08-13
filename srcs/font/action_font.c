#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text(t_doom *doom, t_font *lib, char *message)
{
	lib[0].len = 1;
	lib[0].str = message;
	lib[0].font_rect.x = WIDTH / 12;
	lib[0].font_rect.y = 200;
	lib[0].font_color = doom->lib.font_lib.font_color.green;
}

void		action_font(t_doom *doom, char *message)
{
	t_font		*font_lib;
	TTF_Font *font;
	int			font_size;

	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * 1);
	if (doom->lib.font_lib.game_over_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.game_over_font, message);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 30;
	font_to_sdl(doom, doom->lib.font_lib.game_over_font, font_path, font_size);
}

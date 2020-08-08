#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Key press player movements";
	lib[0].font_rect.x = WIDTH / 12;
	lib[0].font_rect.y = 75;
	lib[0].font_color = doom->lib.font_lib.font_color.black;
	lib[1].str = "Forward = W			Backwards = S			\
	Left = A				Right = D";
	lib[1].font_rect.x = WIDTH / 12;
	lib[1].font_rect.y = 110;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "Jump = Spacebar					Bend = X";
	lib[2].font_rect.x = WIDTH / 12;
	lib[2].font_rect.y = 145;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
}

void	save_instruction_font(t_doom *doom, int *len)
{
	char		*font_path;
	int			font_size;

	*len = 3;
	doom->lib.font_lib.instruction_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.instruction_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.instruction_font, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 18;
	font_to_sdl(doom, doom->lib.font_lib.instruction_font,\
	font_path, font_size);
}

#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_instruction_text_3(t_doom *doom, t_font *lib)
{
	lib[8].str = "Watch out! You tripped over the crate! \
	Jump to stand up.";
	lib[8].font_rect.x = WIDTH / 2 - 235;
	lib[8].font_rect.y = HEIGHT / 2 - 15;
	lib[8].font_color = doom->lib.font_lib.font_color.red;
	lib[9].str = "You're corona level has increased!";
	lib[9].font_rect.x = WIDTH / 2 - 135;
	lib[9].font_rect.y = HEIGHT / 2 + 15;
	lib[9].font_color = doom->lib.font_lib.font_color.green;
}

static void	set_instruction_text_2(t_doom *doom, t_font *lib)
{
	lib[3].str = "Scissor lift operations:";
	lib[3].font_rect.x = WIDTH / 12;
	lib[3].font_rect.y = 65;
	lib[3].font_color = doom->lib.font_lib.font_color.black;
	lib[4].str = "Forward = W			Backwards = S			\
	Left = A				Right = D";
	lib[4].font_rect.x = WIDTH / 12;
	lib[4].font_rect.y = 100;
	lib[4].font_color = doom->lib.font_lib.font_color.black;
	lib[5].str = "UP = up arrow key				DOWN = down arrow key";
	lib[5].font_rect.x = WIDTH / 12;
	lib[5].font_rect.y = 135;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "Exit = Return scissor lift to lowest level and press S.";
	lib[6].font_rect.x = WIDTH / 12;
	lib[6].font_rect.y = 165;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "You're too close to the wall! Reverse and try again.";
	lib[7].font_rect.x = WIDTH / 2 - 100;
	lib[7].font_rect.y = HEIGHT / 2 - 100;
	lib[7].font_color = doom->lib.font_lib.font_color.red;
	set_instruction_text_3(doom, lib);
}

static void	set_instruction_text(t_doom *doom, t_font *lib, int len)
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
	set_instruction_text_2(doom, lib);
}

void	save_instruction_font(t_doom *doom, int *len)
{
	TTF_Font *font;
	int			font_size;

	*len = 10;
	doom->lib.font_lib.instruction_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.instruction_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_instruction_text(doom, doom->lib.font_lib.instruction_font, *len);
	font = doom->lib.font_lib.font_18;
	font_to_sdl(doom, doom->lib.font_lib.instruction_font, font);
}

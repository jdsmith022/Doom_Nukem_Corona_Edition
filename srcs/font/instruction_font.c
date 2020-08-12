#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_instruction_text_4(t_doom *doom, t_font *lib)
{
	lib[10].str = "Keep a look out for the Covid-19 virus!";
	lib[10].font_rect.x = WIDTH / 2 - 160;
	lib[10].font_rect.y = HEIGHT / 2 - 75;
	lib[10].font_color = doom->lib.font_lib.font_color.green;
	lib[11].str = "Press E to enter spray mode and left mouse click\
	to spray sanitizer.";
	lib[11].font_rect.x = WIDTH / 7.5;
	lib[11].font_rect.y = HEIGHT / 2 - 50;
	lib[11].font_color = doom->lib.font_lib.font_color.black;
	lib[12].str = "Press E again to exit spray mode.";
	lib[12].font_rect.x = WIDTH / 2 - 155;
	lib[12].font_rect.y = HEIGHT / 2 - 25;
	lib[12].font_color = doom->lib.font_lib.font_color.black;
	lib[13].str = "Don't worry! You can fill santizer at refill stations.";
	lib[13].font_rect.x = WIDTH / 2 - 200;
	lib[13].font_rect.y = HEIGHT / 2 + 25;
	lib[13].font_color = doom->lib.font_lib.font_color.blue;
	lib[14].str = "Press Q to enter collection mode and left mouse\
	click to collect item.";
	lib[14].font_rect.x = WIDTH / 7.5;
	lib[14].font_rect.y = HEIGHT / 2 + 50;
	lib[14].font_color = doom->lib.font_lib.font_color.black;
	lib[15].str = "Press Q again to exit collection mode.";
	lib[15].font_rect.x = WIDTH / 2 + 120;
	lib[15].font_rect.y = HEIGHT / 2 + 75;
	lib[15].font_color = doom->lib.font_lib.font_color.black;
}

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
	lib[4].font_rect.x = WIDTH / 2 - 120;
	lib[4].font_rect.y = HEIGHT / 2 - 40;
	lib[4].font_color = doom->lib.font_lib.font_color.blue;
	lib[5].str = "UP = up arrow key				DOWN = down arrow key";
	lib[5].font_rect.x = WIDTH / 2 - 20;
	lib[5].font_rect.y = HEIGHT / 2 - 10;
	lib[5].font_color = doom->lib.font_lib.font_color.black;
	lib[6].str = "Exit = Return scissor lift to lowest level and press S.";
	lib[6].font_rect.x = WIDTH / 2 - 200;
	lib[6].font_rect.y = HEIGHT / 2;
	lib[6].font_color = doom->lib.font_lib.font_color.black;
	lib[7].str = "You're too close to the wall! Reverse and try again.";
	lib[7].font_rect.x = WIDTH / 2 - 200;
	lib[7].font_rect.y = HEIGHT / 2 + 20;
	lib[7].font_color = doom->lib.font_lib.font_color.red;
	set_instruction_text_3(doom, lib);
}

static void	set_instruction_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;

	lib[0].len = len;
	lib[0].str = "Key press player movements";
	lib[0].font_rect.x = WIDTH / 2 - 120;
	lib[0].font_rect.y = HEIGHT / 2 - 40;
	lib[0].font_color = doom->lib.font_lib.font_color.blue;
	lib[1].str = "Forward = W			Backwards = S			\
	Left = A				Right = D";
	lib[1].font_rect.x = WIDTH / 2 - 210;
	lib[1].font_rect.y = HEIGHT / 2 - 8;
	lib[1].font_color = doom->lib.font_lib.font_color.black;
	lib[2].str = "Jump = Spacebar					Bend = X";
	lib[2].font_rect.x = WIDTH / 2 - 120;
	lib[2].font_rect.y = HEIGHT / 2 + 20;
	lib[2].font_color = doom->lib.font_lib.font_color.black;
	set_instruction_text_2(doom, lib);
	set_instruction_text_4(doom, lib);
}

void	save_instruction_font(t_doom *doom, int *len)
{
	TTF_Font *font;
	int			font_size;

	*len = 15;
	doom->lib.font_lib.instruction_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (doom->lib.font_lib.instruction_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_instruction_text(doom, doom->lib.font_lib.instruction_font, *len);
	font = doom->lib.font_lib.font_18;
	font_to_sdl(doom, doom->lib.font_lib.instruction_font, font);
}

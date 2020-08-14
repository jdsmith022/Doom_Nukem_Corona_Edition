#include "../../includes/doom.h"
#include "../../includes/font.h"

static void	set_instruction_text_5(t_doom *doom, t_font *lib)
{
	lib[15].str = "Press Q again to exit collection mode.";
	lib[15].font_rect.x = WIDTH / 2 - 150;
	lib[15].font_rect.y = HEIGHT / 2 + 60;
	lib[15].font_color = doom->lib.font_lib.font_color.black;
	lib[16].str = "Please collect a shopping cart.";
	lib[16].font_rect.x = WIDTH / 2 - 150;
	lib[16].font_rect.y = HEIGHT / 2;
	lib[16].font_color = doom->lib.font_lib.font_color.black;
	lib[17].str = "Make sure you're read to checkout!";
	lib[17].font_rect.x = WIDTH / 2 - 140;
	lib[17].font_rect.y = HEIGHT / 2- 10;
	lib[17].font_color = doom->lib.font_lib.font_color.red;
}

void	set_instruction_text_4(t_doom *doom, t_font *lib)
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
	lib[12].font_rect.x = WIDTH / 2 - 145;
	lib[12].font_rect.y = HEIGHT / 2 - 25;
	lib[12].font_color = doom->lib.font_lib.font_color.black;
	lib[13].str = "Don't worry! You can fill santizer at refill stations.";
	lib[13].font_rect.x = WIDTH / 2 - 200;
	lib[13].font_rect.y = HEIGHT / 2 + 10;
	lib[13].font_color = doom->lib.font_lib.font_color.blue;
	lib[14].str = "Press Q to enter collection mode and left mouse\
	click to collect item.";
	lib[14].font_rect.x = WIDTH / 7.5;
	lib[14].font_rect.y = HEIGHT / 2 + 35;
	lib[14].font_color = doom->lib.font_lib.font_color.black;
	set_instruction_text_5(doom, lib);
}

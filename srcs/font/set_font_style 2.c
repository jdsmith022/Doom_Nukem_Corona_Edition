#include "../../includes/doom.h"
#include "../../includes/font.h"

void		set_font_style(t_doom *doom)
{
	TTF_Init();
	doom->lib.font_lib.font_30 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 30);
	doom->lib.font_lib.font_22 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 22);
	doom->lib.font_lib.font_20 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 20);
	doom->lib.font_lib.font_18 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 18);
}

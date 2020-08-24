
#include "../../includes/doom.h"
#include "../../includes/font.h"

void		set_font_style(t_doom *doom)
{
	if (TTF_Init() == -1)
		doom_exit_failure(doom, "SDL_TFF lib init error\n");
	doom->lib.font_lib.font_30 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 30);
	if (doom->lib.font_lib.font_30 == NULL)
		doom_exit_failure(doom, "SLD_TFF lib error\n");
	doom->lib.font_lib.font_22 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 22);
	if (doom->lib.font_lib.font_22 == NULL)
		doom_exit_failure(doom, "SLD_TFF lib error\n");
	doom->lib.font_lib.font_20 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 20);
	if (doom->lib.font_lib.font_20 == NULL)
		doom_exit_failure(doom, "SLD_TFF lib error\n");
	doom->lib.font_lib.font_18 = \
		TTF_OpenFont("srcs/font/font_style/JosefinSans-Bold.ttf", 18);
	if (doom->lib.font_lib.font_18 == NULL)
		doom_exit_failure(doom, "SLD_TFF lib error\n");
}

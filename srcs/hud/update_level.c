#include "../../includes/doom.h"
#include "../../includes/hud.h"

// void	set_timer(t_doom *doom, t_font *lib)
// {
	
// }

void	update_hud_levels(t_doom *doom, t_font *lib)
{
	int		level;
	char	*corona_level;
	char	*cat;
	char	*font_path;
	int		font_size;

	level = doom->hud->corona_level;
	corona_level = ft_itoa(level);
	cat = ft_strcat(corona_level, "%");
	lib[4].str = corona_level;
	lib[4].font_rect.x = 175;
	lib[4].font_rect.y = HEIGHT - 35;
	if (level > 84)
		lib[4].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[4].font_color = doom->lib.font_lib.font_color.white;
	level = doom->hud->sanitizer_level;
	corona_level = ft_itoa(level);
	cat = ft_strcat(corona_level, "%");
	lib[5].str = corona_level;
	lib[5].font_rect.x = WIDTH - 250;
	lib[5].font_rect.y = HEIGHT - 35;
	if (level < 15)
		lib[5].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[5].font_color = doom->lib.font_lib.font_color.white;
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font_path, font_size);
}

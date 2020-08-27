
#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"

static char	*set_seconds(char *timer, char *sec_str)
{
	int		len;
	char	*zero;

	len = ft_strlen(sec_str);
	if (len == 1)
	{
		zero = "0";
		sec_str = ft_strjoin(zero, sec_str);
		timer = ft_strjoin(timer, sec_str);
	}
	else
		timer = ft_strjoin(timer, sec_str);
	return (timer);
}

static char	*time_to_string(t_doom *doom, int time)
{
	char	*timer;
	char	*min_str;
	char	*sec_str;
	int		min;
	int		sec;

	min = time / 60;
	sec = time % 60;
	min_str = ft_itoa(min);
	sec_str = ft_itoa(sec);
	timer = ft_strjoin(min_str, ":");
	return (set_seconds(timer, sec_str));
}

void		update_timer(t_doom *doom, t_font *lib)
{
	TTF_Font	*font;
	int			font_size;
	char		*timer;
	int			time;

	time = doom->hud->curr_time;
	timer = time_to_string(doom, time);
	lib[6].str = "Time:";
	lib[6].font_rect.x = WIDTH / 2.4;
	lib[6].font_rect.y = 15;
	lib[6].font_color = doom->lib.font_lib.font_color.white;
	lib[7].str = timer;
	lib[7].font_rect.x = WIDTH / 1.9;
	lib[7].font_rect.y = 15;
	if (time < 100)
		lib[7].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[7].font_color = doom->lib.font_lib.font_color.white;
	font = doom->lib.font_lib.font_22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font);
	free(timer);
}

static void	update_sanitizer_levels(t_doom *doom, t_font *lib,
				int level, char *sanitizer_level)
{
	lib[5].str = sanitizer_level;
	lib[5].font_rect.x = WIDTH - 250;
	lib[5].font_rect.y = HEIGHT - 35;
	if (level < 15)
		lib[5].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[5].font_color = doom->lib.font_lib.font_color.white;
}

void	update_hud_levels(t_doom *doom, t_font *lib)
{
	TTF_Font	*font;
	int			level;
	char		*corona_level;
	char		*sanitizer_level;
	char		*percent;

	level = doom->hud->corona_level;
	corona_level = ft_itoa(level);
	percent = ft_strcat(corona_level, "%");
	lib[4].str = corona_level;
	lib[4].font_rect.x = 175;
	lib[4].font_rect.y = HEIGHT - 35;
	if (level > 84)
		lib[4].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[4].font_color = doom->lib.font_lib.font_color.white;
	level = doom->hud->sanitizer_level;
	sanitizer_level = ft_itoa(level);
	percent = ft_strcat(sanitizer_level, "%");
	update_sanitizer_levels(doom, lib, level, sanitizer_level);
	font = doom->lib.font_lib.font_22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font);
	free(corona_level);
	free(sanitizer_level);
}

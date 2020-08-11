#include "../../includes/doom.h"
#include "../../includes/menu.h"
#include "../../includes/hud.h"
#include "../../includes/gameplay.h"

static void		missing_groceries(t_doom *doom, t_font *lib)
{
	lib[2].str = "What you missed:";
	lib[2].font_rect.x = WIDTH / 2.7;
	lib[2].font_rect.y = HEIGHT / 3 * 1.7;
	lib[2].font_color = doom->lib.font_lib.font_color.blue;
}

static char		*win_lose_status_2(t_doom *doom, t_font *lib)
{
	char *status;

	status = "You didn't find all you're groceries! \
	Try again!";
	lib[1].font_color = doom->lib.font_lib.font_color.red;
	lib[1].font_rect.x = WIDTH / 12;
	lib[1].font_rect.y = HEIGHT / 2.5;
	missing_groceries(doom, lib);
	return (status);
}

static char		*win_lose_status(t_doom *doom, t_font *lib)
{
	char	*status;

	lib[1].font_rect.x = WIDTH / 14;
	lib[1].font_rect.y = HEIGHT / 2;
	if (doom->groceries->info.won == TRUE && \
	doom->hud->corona_level < 75)
	{
		status = "You found all you're groceries without \
		contracting Corona Virus! Well done!";
		lib[1].font_color = doom->lib.font_lib.font_color.blue;
	}
	else if (doom->groceries->info.won == TRUE && \
	doom->hud->corona_level >= 75)
	{
		status ="Oh no! You contracted the Corona Virus! \
		Self-quarantine immeidately!";
		lib[1].font_color = doom->lib.font_lib.font_color.green;
	}
	else if (doom->groceries->info.won == FALSE)
		status = win_lose_status_2(doom, lib);
	return (status);
}

static void		set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	char		*status;
	char		*score;

	lib[0].len = len;
	lib[0].str = "You're Checked Out";
	lib[0].font_rect.x = WIDTH / 3;
	lib[0].font_rect.y = HEIGHT / 4;
	lib[0].font_color = doom->lib.font_lib.font_color.blue;
	status = win_lose_status(doom, lib);
	lib[1].str = status;
}

void			add_score_to_sdl_text(t_doom *doom)
{
	char		*font_path;
	int			font_size;
	int			len;

	if (doom->groceries->info.won == FALSE)
		len = 3;
	else
		len = 2;
	doom->lib.font_lib.finished_font_len = len;
	len = doom->lib.font_lib.finished_font_len;
	doom->lib.font_lib.finished_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * len);
	if (doom->lib.font_lib.finished_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.finished_font, len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 30;
	font_to_sdl(doom, doom->lib.font_lib.finished_font, \
		font_path, font_size);
}

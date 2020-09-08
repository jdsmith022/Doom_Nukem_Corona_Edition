/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   finished_text.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:14:43 by jesmith       #+#    #+#                 */
/*   Updated: 2020/09/08 12:36:21 by JessicaSmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (doom->groceries)
		missing_groceries(doom, lib);
	return (status);
}

static char		*win_lose_status(t_doom *doom, t_font *lib)
{
	char	*status;

	lib[1].font_rect.x = WIDTH / 8;
	lib[1].font_rect.y = HEIGHT / 2 - 25;
	lib[2].font_rect.x = WIDTH / 4.8;
	lib[2].font_rect.y = HEIGHT / 2 + 25;
	if (doom->groceries->info.won == TRUE && \
	doom->hud->corona_level < 75)
	{
		status = "Well done! You found all you're groceries";
		lib[1].font_color = doom->lib.font_lib.font_color.blue;
		lib[2].str = "without contracting Covid-19!";
		lib[2].font_color = doom->lib.font_lib.font_color.blue;
	}
	else if (doom->groceries->info.won == TRUE && \
	doom->hud->corona_level >= 75)
	{
		status = "Oh no! Looks like you contracted Covid-19!";
		lib[1].font_color = doom->lib.font_lib.font_color.green;
		lib[2].str = "Self-quarantine immeidately!";
		lib[2].font_color = doom->lib.font_lib.font_color.green;
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
	lib[0].font_rect.x = WIDTH / 3.2;
	lib[0].font_rect.y = HEIGHT / 4;
	lib[0].font_color = doom->lib.font_lib.font_color.blue;
	status = win_lose_status(doom, lib);
	lib[1].str = status;
	lib[3].str = "Press ESC to exit";
	lib[3].font_rect.x = WIDTH / 2.8;
	lib[3].font_rect.y = HEIGHT - 100;
	lib[3].font_color = doom->lib.font_lib.font_color.red;
}

void			add_score_to_sdl_text(t_doom *doom)
{
	TTF_Font	*font;
	int			font_size;
	int			len;

	len = 4;
	doom->lib.font_lib.finished_font_len = len;
	len = doom->lib.font_lib.finished_font_len;
	doom->lib.font_lib.finished_font = \
		(t_font*)ft_memalloc(sizeof(t_font) * len);
	if (doom->lib.font_lib.finished_font == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_text(doom, doom->lib.font_lib.finished_font, len);
	font = doom->lib.font_lib.font_30;
	font_to_sdl(doom, doom->lib.font_lib.finished_font, \
		font);
}

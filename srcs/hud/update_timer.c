/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   update_timer.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/28 15:16:05 by jesmith       #+#    #+#                 */
/*   Updated: 2020/08/29 16:19:24 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"
#include "../../includes/hud.h"
#include "../../includes/font.h"

static char	*set_seconds(char *timer, char *sec_str)
{
	int		len;
	char	*new_str;
	char	*new_time;

	len = ft_strlen(sec_str);
	if (len == 1)
	{
		new_str = ft_strjoin("0", sec_str);
		free(sec_str);
		new_time = ft_strjoin(timer, new_str);
		free(timer);
		free(new_str);
	}
	else
	{
		new_time = ft_strjoin(timer, sec_str);
		free(timer);
		free(sec_str);
	}
	return (new_time);
}

static void	get_time(int time, char **min_str, char **sec_str)
{
	int		min;
	int		sec;

	min = time / 60;
	sec = time % 60;
	*min_str = ft_itoa(min);
	*sec_str = ft_itoa(sec);
}

static char	*time_to_string(t_doom *doom, int time)
{
	char	*timer;
	char	*new;
	char	*min_str;
	char	*sec_str;

	get_time(time, &min_str, &sec_str);
	timer = ft_strjoin(min_str, ":");
	free(min_str);
	new = set_seconds(timer, sec_str);
	return (new);
}

void		update_timer(t_doom *doom, t_font *lib)
{
	TTF_Font	*font;
	int			font_size;
	char		*timer;
	char		*new_time;
	int			time;

	time = doom->hud->curr_time;
	timer = time_to_string(doom, time);
	new_time = ft_strjoin("Time:	", timer);
	free(timer);
	lib[6].str = new_time;
	free(new_time);
	if (time < 100)
		lib[6].font_color = doom->lib.font_lib.font_color.red;
	else
		lib[6].font_color = doom->lib.font_lib.font_color.white;
	font = doom->lib.font_lib.font_22;
	single_font_to_sdl(doom, doom->lib.font_lib.hud_font[6], font);
}

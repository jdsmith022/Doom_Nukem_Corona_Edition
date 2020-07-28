/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:40:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/26 17:55:44 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_menu_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		**str;

	index = 0;
	lib[index].len = len;
	lib[index].str = "Create Sector";
	lib[index].font_rect.x = 30;
	lib[index].font_rect.y = 40;
	lib[index].font_color = doom->lib.font_lib.font_color.black;
	index++;
	lib[index].str = "Design Sector";
	lib[index].font_rect.x = 670;
	lib[index].font_rect.y = 40;
	lib[index].font_color = doom->lib.font_lib.font_color.black;
}

static t_font	*editor_menu(t_doom *doom, int *len)
{
	t_font		*font_lib;

	*len = 2;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_menu_text(doom, font_lib, *len);
	return (font_lib);
}

static void	set_info_text(t_doom *doom, t_font *lib, char **info, int len)
{
	SDL_Rect	font_rect;
	size_t		index;

	index = 0;
	lib[index].font_rect.x = 40;
	lib[index].font_rect.y = 40;
	lib[index].len = len;
	while (index < len)
	{
		lib[index].str = info[index];
		lib[index].font_color = doom->lib.font_lib.font_color.black;
		lib[index].font_rect.y = (20 * (index + 1));
		index++;
	}
}

static t_font	*editor_info(t_doom *doom, char **info, int len)
{
	t_font		*font_lib;

	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * len);
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	set_info_text(doom, font_lib, info, len);
	return (font_lib);
}

static void	create_info_string(char **str, int *len)
{
	str[0] = "How to create a map.";
	str[1] = "To create a map, do the following.";
	str[2] = "isn't this great.";
	*len = 3;
}

void		save_game_editor_font(t_doom *doom, int *len)
{
	char		*font_path;
	char		**info;
	int			font_size;

	// if (doom->own_event.editor_info == TRUE)
	// {
		// create_info_string(info, len);
		// doom->lib.font_lib.game_editor_font = editor_info(doom, info, *len);
	// }
	// else
	doom->lib.font_lib.game_editor_font = editor_menu(doom, len);
	font_path = "srcs/font/font_style/Cicle_Semi.ttf";
	font_size = 20;
	font_to_sdl(doom, doom->lib.font_lib.game_editor_font,\
		font_path, font_size);
}

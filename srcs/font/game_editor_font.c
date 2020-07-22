/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   game_editor_font.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 14:40:40 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/22 22:23:12 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		**str;

	index = 0;
	lib[index].str = "Select texture";
	lib[index].font_rect.x = 100;
	lib[index].font_rect.y = 300;
	lib[index].font_color = doom->lib.font_color.white;
	index++;
	lib[index].str= "Select objects";
	lib[index].font_rect.x = 300;
	lib[index].font_rect.y = 300;
}

void		save_game_editor_font(t_doom *doom, int *len)
{
	t_font		*font_lib;
	SDL_Color	font_color;

	*len = 2;
	font_lib = doom->lib.game_editor_font;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.game_editor_font = font_lib;
	set_text(doom, font_lib, *len);
	font_to_surface(doom, doom->lib.game_editor_font, *len);
}

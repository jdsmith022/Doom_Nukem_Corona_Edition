/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 23:02:29 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/23 10:41:39 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		**str;

	index = 0;
	lib[index].len = len;
	lib[index].str = "Corona Level";
	lib[index].font_rect.x = 30;
	lib[index].font_rect.y = 520;
	lib[index].font_color = doom->lib.font_lib.font_color.green;
	index++;
	lib[index].str = "Sanitizer Level";
	lib[index].font_rect.x = 620;
	lib[index].font_rect.y = 520;
	lib[index].font_color = doom->lib.font_lib.font_color.blue;
	index++;
	lib[index].str = "Shopping List";
	lib[index].font_rect.x = 30;
	lib[index].font_rect.y = 50;
	lib[index].font_color = doom->lib.font_lib.font_color.red;
	index++;
	lib[index].str = "Basket";
	lib[index].font_rect.x = 30;
	lib[index].font_rect.y = 100;
	lib[index].font_color = doom->lib.font_lib.font_color.red;
}

void		save_hud_font(t_doom *doom, int *len)
{
	t_font		*font_lib;
	char		*font_path;
	int			font_size;

	*len = 4;
	font_lib = doom->lib.font_lib.hud_font;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.font_lib.hud_font = font_lib;
	set_text(doom, font_lib, *len);
	font_path = "srcs/font/font_style/JosefinSans-Bold.ttf";
	font_size = 22;
	font_to_sdl(doom, doom->lib.font_lib.hud_font, font_path, font_size);
}

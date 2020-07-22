/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   hud_font.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jessicasmith <jessicasmith@student.coda      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/22 23:02:29 by jessicasmit   #+#    #+#                 */
/*   Updated: 2020/07/22 23:24:14 by jessicasmit   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_text(t_doom *doom, t_font *lib, int len)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		**str;

	index = 0;
	lib[index].str = "Corona Level";
	lib[index].font_rect.x = 30;
	lib[index].font_rect.y = 520;
	lib[index].font_color = doom->lib.font_color.green;
	index++;
	lib[index].str= "Sanitizer Level";
	lib[index].font_rect.x = 620;
	lib[index].font_rect.y = 520;
	lib[index].font_color = doom->lib.font_color.red;
}

void		save_hud_font(t_doom *doom, int *len)
{
	t_font		*font_lib;
	SDL_Color	font_color;
	char		*font_path;
	int			font_size;

	*len = 2;
	font_lib = doom->lib.hud_font;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	doom->lib.hud_font = font_lib;
	set_text(doom, font_lib, *len);
	font_path = "srcs/font/font_style/Cicle_Semi.ttf";
	font_size = 26;
	font_to_surface(doom, doom->lib.hud_font, *len, font_path, font_size);
}

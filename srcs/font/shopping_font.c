/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shopping_font.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: jesmith <jesmith@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 09:40:21 by jesmith       #+#    #+#                 */
/*   Updated: 2020/07/23 13:33:52 by jesmith       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/doom.h"

static void	set_text(t_doom *doom, t_font *lib, int len, char **shopping_list)
{
	SDL_Rect	font_rect;
	size_t		index;
	char		*list_tally;
	char		**str;

	index = 0;
	lib[index].font_rect.x = 40;
	lib[index].font_rect.y = 40;
	while (index < len)
	{
		lib[index].str = shopping_list[index];
		lib[index].font_color = doom->lib.font_lib.font_color.black;
		lib[index].font_rect.x += 20;
		if (lib[index].font_rect.x == 150)
			lib[index].font_rect.y += 75;
		index++;
	}
}

void		save_shopping_list_font(t_doom *doom, int *len)
{
	t_font		*font_lib;
	char		*font_path;
	int			font_size;
	char		**shopping_list;

	doom->lib.font_lib.items_in_basket = 1;
	font_lib = (t_font*)ft_memalloc(sizeof(t_font) * (*len));
	if (font_lib == NULL)
		doom_exit_failure(doom, MALLOC_ERR);
	*len = doom->lib.len_obj_lib;
	font_lib = doom->lib.font_lib.basket_font;
	set_text(doom, font_lib, *len, doom->lib.font_lib.shopping_list);
	font_path = "srcs/font/font_style/AmaticSC-Regular.ttf";
	font_size = 26;
	doom->lib.font_lib.basket_font = font_lib;
	font_to_sdl(doom, doom->lib.font_lib.basket_font, font_path, font_size);
}
